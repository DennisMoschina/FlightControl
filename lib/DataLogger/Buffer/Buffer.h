#ifndef _BUFFER_H_
#define _BUFFER_H_

template<typename T>
class BufferIterator;

template<typename T>
class Buffer {
public:
    virtual void add(T element) = 0;

    virtual BufferIterator<T>* iterator() = 0;
    virtual size_t getSize() = 0;

    virtual T getAt(size_t index);
};


template<typename T>
class BufferIterator {
public:
    BufferIterator(Buffer<T>* buffer) {
        this->buffer = buffer;
    };

    virtual bool hasNext() = 0;
    virtual T next() = 0;

protected:
    Buffer<T>* buffer;
};

#endif