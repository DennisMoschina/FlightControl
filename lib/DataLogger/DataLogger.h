#ifndef _DATA_LOGGER_H_
#define _DATA_LOGGER_H_

#include "Buffer/Buffer.h"

template<typename T>
class DataLogger {
public:
    DataLogger(Buffer<T>* buffer);

    void log(T data);

    size_t getLoggedSize();
    T* getLogged();

private:
    Buffer<T>* buffer;
};

//=================================================

template<typename T>
DataLogger<T>::DataLogger(Buffer<T>* buffer) {
    this->buffer = buffer;
}

template<typename T>
void DataLogger<T>::log(T data) {
    this->buffer->add(data);
}

template<typename T>
size_t DataLogger<T>::getLoggedSize() {
    return this->buffer->getSize();
}

template<typename T>
T* DataLogger<T>::getLogged() {
    size_t loggedSize = this->getLoggedSize();

    T* logged = malloc(sizeof(T) * loggedSize);
    BufferIterator<T>* iterator = this->buffer->iterator();
    for (int i = 0; i < loggedSize; i++) {
        logged[i] = iterator->next();
    }
    return logged;
}

#endif