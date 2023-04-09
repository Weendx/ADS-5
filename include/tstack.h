// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template<typename T, int kSize>
class TStack {
    T arr[kSize];
    int top;

 public:
    TStack() : top(-1) {}

    void push(const T value) {
        if (isFull())
            throw std::domain_error("TStack::push(): Stack overflow!");
        arr[++top] = value;
    }

    T get() const {
        if (isEmpty())
            throw std::logic_error("TStack::get(): Stack is Empty!");
        return arr[top];
    }

    T pop() {
        if (isEmpty())
            throw std::logic_error("TStack::pop(): Stack is Empty!");
        return arr[top--];
    }

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == kSize; }
};

#endif  // INCLUDE_TSTACK_H_
