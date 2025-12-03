#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

template <class T>
class List {
private:
    template <class U>
    class Link {
    public:
        U value;
        Link<U> *next;
        
        Link(U val) : value(val), next(nullptr) {}
    };
    
    Link<T> *head;
    int size;

public:
    List() : head(nullptr), size(0) {}
    
    ~List() {
        clear();
    }
    
    void insertion(T value) {
        Link<T> *newLink = new Link<T>(value);
        
        if (head == nullptr) {
            head = newLink;
        } else {
            Link<T> *current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newLink;
        }
        size++;
    }
    
    int search(T value) const {
        Link<T> *current = head;
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
    
    void update(int position, T newValue) {
        if (position < 0 || position >= size) {
            throw out_of_range("Posición inválida");
        }
        
        Link<T> *current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        current->value = newValue;
    }
    
    T deleteAt(int position) {
        if (position < 0 || position >= size) {
            throw out_of_range("Posición inválida");
        }
        
        Link<T> *current = head;
        Link<T> *previous = nullptr;
        T deletedValue;
        
        if (position == 0) {
            head = head->next;
            deletedValue = current->value;
            delete current;
        } else {
            for (int i = 0; i < position; i++) {
                previous = current;
                current = current->next;
            }
            previous->next = current->next;
            deletedValue = current->value;
            delete current;
        }
        
        size--;
        return deletedValue;
    }
    
    std::string toString() const {
        std::stringstream aux;
        Link<T> *p;

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
    
    void clear() {
        Link<T> *current = head;
        while (current != nullptr) {
            Link<T> *temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        size = 0;
    }
    
    int getSize() const {
        return size;
    }
};

#endif