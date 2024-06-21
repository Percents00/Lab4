#ifndef MUTABLESEQUENCE_H
#define MUTABLESEQUENCE_H

template <typename T>
class MutableSequence {
public:
    virtual ~MutableSequence() = default;

    virtual const T &Get(int index) const = 0;
    virtual const T &GetFirst() const = 0;
    virtual const T &GetLast() const = 0;
    
    virtual int GetLength() const = 0;
    virtual void Append(const T item) = 0;
    virtual void Prepend(const T item) = 0;
    virtual void InsertAt(int index, const T item) = 0;
    virtual void Concatenate(MutableSequence<T> *sequence) = 0;

    virtual MutableSequence<T> *GetSubSequence(int startIndex, int endIndex) = 0;
};


#endif