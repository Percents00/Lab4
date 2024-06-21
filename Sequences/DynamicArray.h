#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdexcept>

template <class T>
class DynamicArray {
    private:
        T* data;
        int size;

    public:
        DynamicArray(T* data, int count) : size(count), data(new T[size]) {
            for (int i = 0; i < count; i++) {
                this->data[i] = data[i];
            }
        }

        DynamicArray(int size) : size(size), data(new T[size]) {}

        DynamicArray(DynamicArray<T> & dynamicArray) : size(dynamicArray.size), data(new T[size]) {
            for (int i = 0; i < size; i++) {
                this->data[i] = dynamicArray.data[i];
            }
        }

        ~DynamicArray() { delete[] data; }

        T& Get(int index) { 
            if (index < 0 || index >= size) {
                throw std::out_of_range("IndexOutOfRange");
            }
            return data[index];
        }

        int GetSize() const {
            return size;
        }

        void Set(int index, T value) {
            if (index < 0 || index >= size) {
                throw std::out_of_range("IndexOutOfRange");
            }
            data[index] = value;
        }

        void Resize(int newSize) {
            T *newData = new T[newSize];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            size = newSize;
        }


};


#endif