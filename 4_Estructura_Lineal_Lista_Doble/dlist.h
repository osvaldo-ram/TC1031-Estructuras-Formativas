#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

template <class T>
class DList {
private:
    template <class U>
    class DLink {
    public:
        U value;
        DLink<U> *next;
        DLink<U> *previous;
        
        DLink(U val) : value(val), next(nullptr), previous(nullptr) {}
    };
    
    DLink<T> *head;
    DLink<T> *tail;
    int size;

public:
    DList() : head(nullptr), tail(nullptr), size(0) {}
    
    ~DList() {
        clear();
    }
    
    void insertion(T value);
    int search(T value) const;
    void update(int position, T newValue);
    T deleteAt(int position);
    
    std::string toStringForward() const;
    std::string toStringBackward() const;
    
    void clear();
    int getSize() const;
};

template <class T>
std::string DList<T>::toStringForward() const {
    std::stringstream aux;
    DLink<T> *p;

    p = head;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->next != 0) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
    std::stringstream aux;
    DLink<T> *p;

    p = tail;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->previous != 0) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}

template <class T>
void DList<T>::insertion(T value) {
    DLink<T> *newLink = new DLink<T>(value);
    
    if (head == nullptr) {
        head = newLink;
        tail = newLink;
    } else {
        tail->next = newLink;
        newLink->previous = tail;
        tail = newLink;
    }
    size++;
}

template <class T>
int DList<T>::search(T value) const {
    DLink<T> *current = head;
    int position = 0;
    
    while (current != nullptr) {
        if (current->value == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1;
}

template <class T>
void DList<T>::update(int position, T newValue) {
    if (position < 0 || position >= size) {
        throw out_of_range("Posición inválida");
    }
    
    DLink<T> *current = head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    current->value = newValue;
}

template <class T>
T DList<T>::deleteAt(int position) {
    if (position < 0 || position >= size) {
        throw out_of_range("Posición inválida");
    }
    
    DLink<T> *current = head;
    T deletedValue;
    
    if (position == 0) {
        head = head->next;
        if (head != nullptr) {
            head->previous = nullptr;
        } else {
            tail = nullptr;
        }
        deletedValue = current->value;
        delete current;
    } else if (position == size - 1) {
        current = tail;
        tail = tail->previous;
        tail->next = nullptr;
        deletedValue = current->value;
        delete current;
    } else {
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        current->previous->next = current->next;
        current->next->previous = current->previous;
        deletedValue = current->value;
        delete current;
    }
    
    size--;
    return deletedValue;
}

template <class T>
void DList<T>::clear() {
    DLink<T> *current = head;
    while (current != nullptr) {
        DLink<T> *temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <class T>
int DList<T>::getSize() const {
    return size;
}

#endif