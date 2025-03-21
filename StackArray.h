#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include <iostream>
#include "Stack.h"
#include "stackExceptions.h"

template<class T>
class StackArray: public Stack<T> {
public:

    StackArray(const int capacity):
        capacity_(capacity),
        size_(0)
    {
        if (capacity_ <= 0) {
            throw WrongStackSize();
        }
        array_ = new T[capacity_];
    }

    StackArray(const StackArray &other):
        capacity_(other.capacity_),
        size_(other.size_)
    {
        array_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            array_[i] = other.array_[i];
        }
    }

    StackArray(const StackArray &&other) noexcept:
        capacity_(other.capacity_),
        size_(other.size_),
        array_(other.array_)
    {

    }

    ~StackArray() override {
        delete[] array_;
    }

    StackArray& operator=(const StackArray &other) {
        if (this != &other) {
            StackArray otherCopy(other);
            swap(otherCopy);
        }
        return *this;
    }

    StackArray& operator=(StackArray &&other) noexcept {
        if (this != &other) {
            StackArray otherCopy(std::move(other));
            swap(otherCopy);
        }
        return *this;
    }

    void push(const T &element) override {
        if (size_ == capacity_) {
            throw StackOverflow();
        }
        array_[size_++] = element;
    }

    T pop() override {
        if (size_ == 0) {
            throw StackUnderflow();
        }
        T result = array_[--size_];
        return result;
    }

    T peek() {
        if (size_ == 0) {
            throw StackUnderflow();
        }
        return array_[size_-1];
    }

    bool isEmpty() const override {
        return size_ == 0;
    }

    template <typename T1>
    friend std::ostream& operator<<(std::ostream& os, const StackArray<T1>& stackArray);

private:
    int capacity_;
    int size_;
    T *array_;

    void swap(StackArray& other) noexcept {
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(array_, other.array_);
    }
};

template <class T>
std::ostream& operator<<(std::ostream& os, const StackArray<T>& stackArray) {
    os << "bottom-> ";
    for (int i = 0; i < stackArray.size_; ++i) {
        os << stackArray.array_[i] << " ";
    }
    os << "<-top\n";
    return os;
}

#endif //STACK_ARRAY_H
