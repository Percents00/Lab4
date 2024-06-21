#ifndef MUTABLEARRAYSEQUENCE_H
#define MUTABLEARRAYSEQUENCE_H

#include "MutableSequence.h"
#include "DynamicArray.h"

template <typename T>
class MutableArraySequence : public MutableSequence<T> {
private:
    DynamicArray<T>* array;

public:
    MutableArraySequence() : array(new DynamicArray<T>(0)) {}

    MutableArraySequence(T* items, int count) : array(new DynamicArray<T>(items, count)) {}

    MutableArraySequence(const MutableArraySequence<T>& other) : array(new DynamicArray<T>(*other.array)) {}

    MutableArraySequence(DynamicArray<T>* arr) : array(arr) {}  

    ~MutableArraySequence() {
        delete array;
    }

    T& Get(int index) { 
        return array->Get(index);
    }

    const T& Get(int index) const { 
        return array->Get(index);
    }

    const T& GetFirst() const override {
        if (array->GetSize() == 0) {
            throw std::out_of_range("SequenceIsEmpty");
        }
        return array->Get(0);
    }

    const T& GetLast() const override {
        if (array->GetSize() == 0) {
            throw std::out_of_range("SequenceIsEmpty");
        }
        return array->Get(array->GetSize() - 1);
    }

    int GetLength() const override {
        return array->GetSize();
    }

    void Append(T item) override { 
        int oldSize = array->GetSize();
        array->Resize(oldSize + 1);
        array->Set(oldSize, item);
    }

    void Prepend(T item) override {
        int oldSize = array->GetSize();
        array->Resize(oldSize + 1);
        for (int i = oldSize; i > 0; --i) {
            array->Set(i, array->Get(i - 1));
        }
        array->Set(0, item);
    }

    void InsertAt(int index, T item) override {
        if (index < 0 || index > array->GetSize()) {
            throw std::out_of_range("IndexOutOfRange");
        }
        int oldSize = array->GetSize();
        array->Resize(oldSize + 1);
        for (int i = oldSize; i > index; --i) {
            array->Set(i, array->Get(i - 1));
        }
        array->Set(index, item);
    }

    MutableArraySequence<T>* GetSubSequence(int startIndex, int endIndex) override {
        if (startIndex < 0 || endIndex >= array->GetSize() || startIndex > endIndex) {
            throw std::out_of_range("IndexOutOfRange");
        }
        int newSize = endIndex - startIndex + 1;
        auto* newArray = new DynamicArray<T>(newSize);
        for (int i = 0; i < newSize; ++i) {
            newArray->Set(i, array->Get(startIndex + i));
        }
        return new MutableArraySequence<T>(newArray); 
    }

    void Concatenate(MutableSequence<T>* sequence) override {
        int oldSize = array->GetSize();
        int sequenceSize = sequence->GetLength();
        array->Resize(oldSize + sequenceSize);
        for (int i = 0; i < sequenceSize; ++i) {
            array->Set(oldSize + i, sequence->Get(i));
        }
    }
};

#endif