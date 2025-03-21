#ifndef POSTFIX_FROM_INFIX_H
#define POSTFIX_FROM_INFIX_H

#include "StackArray.h"

class InvalidInfixCharException: public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: invalid characters in infix arithmetic expression.\n";
    }
};

class InvalidInfixChainException: public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: chain of infix arithmetic expression is invalid.\n";
    }
};

class InvalidInfixBracketsException: public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: invalid brackets pairs in infix arithmetic expression.\n";
    }
};

class DivisionByZeroException: public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: division by zero in infix arithmetic expression.\n";
    }
};

int getOperatorPriority(const char& ch) {
    if (ch == '(') {
        return 0;
    }
    if (ch == ')') {
        return 1;
    }
    if (ch == '+') {
        return 2;
    }
    if (ch == '-') {
        return 2;
    }
    if (ch == '*') {
        return 3;
    }
    if (ch == '/') {
        return 3;
    }
    return 0;
}

bool isOperator(const char& ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isBracket(const char& ch) {
    return ch == ')' || ch == '(';
}

bool isDigit(const char &ch) {
    return ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7'
            || ch =='8' || ch == '9';
}

void getPostfixFromInfix(const char* infix, char* postfix, const size_t stackSize) {
    StackArray<char> stack(static_cast<int>(stackSize));

    bool isPreviousCharDigit = false;
    bool isPreviousCharOperator = false;
    bool isPreviousCharOpenBracket = false;
    bool isPreviousCharCloseBracket = false;

    int resultIndex = 0;
    int i = 0;
    while (infix[i] != '\0') {
        if (i == 0 && (infix[i] == '*' || infix[i] == '/')) {
            throw InvalidInfixChainException();
        }

        if (infix[i] == '/' && infix[i+1] == '0') {
            throw DivisionByZeroException();
        }

        char currentInfixChar = infix[i];

        if (isDigit(currentInfixChar)) {
            if (isPreviousCharDigit) {
                throw InvalidInfixChainException();
            }
            if (isPreviousCharCloseBracket) {
                throw InvalidInfixChainException();
            }

            postfix[resultIndex++] = currentInfixChar;
            isPreviousCharOperator = false;
            isPreviousCharCloseBracket = false;
            isPreviousCharOpenBracket = false;
            isPreviousCharDigit = true;
            ++i;
            continue;
        }

        if (isOperator(currentInfixChar)) {
            if (isPreviousCharOperator) {
                throw InvalidInfixChainException();
            }
            if (isPreviousCharOpenBracket) {
                throw InvalidInfixChainException();
            }

            if (stack.isEmpty()) {
                stack.push(currentInfixChar);
            }
            else {
                const int currentPriority = getOperatorPriority(currentInfixChar);
                while(!stack.isEmpty() && getOperatorPriority(stack.peek()) >= currentPriority) {
                    postfix[resultIndex++] = stack.pop();
                }
                stack.push(currentInfixChar);
            }
            isPreviousCharOperator = true;
            isPreviousCharCloseBracket = false;
            isPreviousCharOpenBracket = false;
            isPreviousCharDigit = false;
            ++i;
            continue;
        }

        if (isBracket(currentInfixChar)) {
            if (isPreviousCharOperator && currentInfixChar == ')') {
                throw InvalidInfixChainException();
            }
            if (isPreviousCharDigit && currentInfixChar == '(') {
                throw InvalidInfixChainException();
            }

            if (currentInfixChar == '(') {
                stack.push(currentInfixChar);
            }
            else {
                while (!stack.isEmpty() && stack.peek() != '(') {
                    postfix[resultIndex++] = stack.pop();
                }
                if (stack.isEmpty()) {
                    throw InvalidInfixBracketsException();
                }
                else {
                    stack.pop();
                }
            }

            isPreviousCharOperator = false;
            isPreviousCharDigit = false;
            isPreviousCharCloseBracket = currentInfixChar == ')';
            isPreviousCharOpenBracket = currentInfixChar == '(';
            ++i;
            continue;
        }
        throw InvalidInfixCharException();
    }

    if (isPreviousCharOperator || isPreviousCharOpenBracket) {
        throw InvalidInfixChainException();
    }
    while (!stack.isEmpty()) {
        const char ch = stack.pop();
        if (ch == '(') {
            throw InvalidInfixBracketsException();
        }
        postfix[resultIndex++] = ch;
    }
    postfix[resultIndex++] = '\0';
}



#endif //POSTFIX_FROM_INFIX_H
