#ifndef _ARRAY_BUFFER_H_
#define _ARRAY_BUFFER_H_

#include "Buffer/Buffer.h"

template<typename T>
class ArrayBufferIterator;

template<typename T, size_t SIZE>
class ArrayBuffer: public Buffer<T> {
public:
    void add(T element);

    BufferIterator<T>* iterator();
    size_t getSize();

    T getAt(size_t index);
    
private:
    T array[SIZE];
    size_t index;
};

template<typename T>
class ArrayBufferIterator: public BufferIterator<T> {
public:
    ArrayBufferIterator(Buffer<T>* buffer): BufferIterator<T>(buffer) {
    };

    bool hasNext();
    T next();

private :
    size_t index = 0;
};

//===============================

template<typename T, size_t SIZE>
void ArrayBuffer<T, SIZE>::add(T element) {
    if (this->index < SIZE) {
        this->array[this->index++] = element;
    }
}

template<typename T, size_t SIZE>
BufferIterator<T>* ArrayBuffer<T, SIZE>::iterator() {
    return new ArrayBufferIterator<T>(this);
}

template<typename T, size_t SIZE>
size_t ArrayBuffer<T, SIZE>::getSize() {
    return SIZE;
}

template<typename T, size_t SIZE>
T ArrayBuffer<T, SIZE>::getAt(size_t index) {
    return this->array[index];
}


template<typename T>
bool ArrayBufferIterator<T>::hasNext() {
    return this->index < this->buffer->getSize();
}


template<typename T>
T ArrayBufferIterator<T>::next() {
    if (this->hasNext()) {
        return this->buffer->getAt(this->index++);
    }
}


#endif