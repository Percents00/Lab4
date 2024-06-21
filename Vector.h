#pragma once

#include "Sequences/MutableArraySequence.h"
#include <cmath>

template <typename T>
class Vector {
    private:
        MutableArraySequence<T>* coordinates;


    public:
        Vector() : coordinates(new MutableArraySequence<T>()) {}

        Vector(T *items, int length) : coordinates(new MutableArraySequence<T>(items, length)) {}

        Vector(const Vector<T>& other) : coordinates(new MutableArraySequence<T>(*other.coordinates)) {} 

        Vector(int length) : coordinates(new MutableArraySequence<T>(new DynamicArray<T>(length))) {} 

        ~Vector() {
            delete coordinates;
        }

        int GetDimension() const {
            return coordinates->GetLength();
        }

        void append(const T &item) {
            coordinates->Append(item);
        }

        T& operator[](int index) {
            if (index < 0 || index >= GetDimension()) {
                throw std::out_of_range("IndexOutOfRange");
            }
            return coordinates->Get(index);
        }

        const T& operator[](int index) const {
            if (index < 0 || index >= GetDimension()) {
                throw std::out_of_range("IndexOutOfRange");
            }
            return coordinates->Get(index);
        }

        Vector<T> operator+(const Vector<T>& other) const {
            if (GetDimension() != other.GetDimension()) {
                throw std::invalid_argument("Different dimensions ");
            }

            Vector<T> result(GetDimension());
            for (int i = 0; i < GetDimension(); ++i) {
                result[i] = (*this)[i] + other[i];
            }
            return result;
        }

        Vector<T> operator*(const T& scalar) const {
            Vector<T> result(GetDimension());
            for (int i = 0; i < GetDimension(); ++i) {
                result[i] = (*this)[i] * scalar;
            }
            return result;
        }

        double Norm() const {
            T sum = 0;
            for (int i = 0; i < GetDimension(); ++i) {
                sum += (*this)[i] * (*this)[i]; 
            }
            return std::sqrt(sum);
        }

        T operator*(const Vector<T>& other) const {
            if (GetDimension() != other.GetDimension()) {
                throw std::invalid_argument("Vectors must have the same dimension for dot product.");
            }

            T result = 0;
            for (int i = 0; i < GetDimension(); ++i) {
                result += (*this)[i] * other[i];
            }
            return result;
        }
};