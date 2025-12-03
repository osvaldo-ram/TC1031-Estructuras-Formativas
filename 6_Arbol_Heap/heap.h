#ifndef HEAP_H
#define HEAP_H
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

template <class T>
class Heap {
private:
    T* data;
    int capacity;
    int count;
    
    int parent(int i) const { return (i - 1) / 2; }
    int left(int i) const { return 2 * i + 1; }
    int right(int i) const { return 2 * i + 2; }
    
    void siftUp(int i) {
        while (i > 0 && data[i] < data[parent(i)]) {
            std::swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }
    
    void siftDown(int i) {
        int minIndex = i;
        int l = left(i);
        if (l < count && data[l] < data[minIndex]) {
            minIndex = l;
        }
        int r = right(i);
        if (r < count && data[r] < data[minIndex]) {
            minIndex = r;
        }
        if (i != minIndex) {
            std::swap(data[i], data[minIndex]);
            siftDown(minIndex);
        }
    }

public:
    Heap(int capacity) : capacity(capacity), count(0) {
        data = new T[capacity];
    }
    
    ~Heap() {
        delete[] data;
    }
    
    void push(T n) {
        if (count == capacity) {
            throw std::out_of_range("Heap lleno");
        }
        data[count] = n;
        siftUp(count);
        count++;
    }
    
    void pop() {
        if (empty()) {
            throw std::out_of_range("Heap vacío");
        }
        data[0] = data[count - 1];
        count--;
        if (count > 0) {
            siftDown(0);
        }
    }
    
    T top() const {
        if (empty()) {
            throw std::out_of_range("Heap vacío");
        }
        return data[0];
    }
    
    bool empty() const {
        return count == 0;
    }
    
    int size() const {
        return count;
    }
    
    std::string toString() const {
        std::stringstream aux;
        aux << "[";
        for (unsigned int i = 0; i < count; i++) {
            if (i != 0) {
                aux << " ";
            }
            aux << data[i];
        }
        aux << "]";
        return aux.str();
    }
};
#endif