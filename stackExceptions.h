#ifndef STACK_EXCEPTIONS_H
#define STACK_EXCEPTIONS_H

#include <stdexcept>

class StackOverflow final: public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: stack overflow.\n";
    }
};

class StackUnderflow final: public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: stack underflow.\n";
    }
};

class WrongStackSize final: public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: wrong stack size.\n";
    }
};

#endif //STACK_EXCEPTIONS_H
