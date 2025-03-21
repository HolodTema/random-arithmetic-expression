#include <iostream>
#include <random>
#include <chrono>
#include <stdexcept>

#include "postfixFromInfix.h"

char* generateRandomExpression(int maxLen) {
    const char* ALPHABET = "0123456789++--**//(())\0";

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed);

    int randomResultLen = generator() % maxLen;
    if (randomResultLen == 0) {
        randomResultLen ++;
    }

    char* result = new char[randomResultLen+1];
    for (int i = 0; i < randomResultLen; ++i) {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator.seed(seed);

        int randomCharIndex = generator() % 22;
        result[i] = ALPHABET[randomCharIndex];
    }
    result[randomResultLen] = '\0';
    return result;
}

char* generateRandomSingleDigitExpression(int maxLen) {
    const char* ALPHABET = "0123456789+-*/()\0";

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed);

    int randomResultLen = generator() % maxLen;
    if (randomResultLen == 0) {
        randomResultLen ++;
    }

    int previousCharIndex = -1;
    char* result = new char[randomResultLen+1];
    for (int i = 0; i < randomResultLen; ++i) {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator.seed(seed);

        int randomCharIndex = 0;
        if (previousCharIndex <= 9) {
            randomCharIndex = generator() % 6 + 10;
        }
        else {
            randomCharIndex = generator() % 16;
        }

        result[i] = ALPHABET[randomCharIndex];
        previousCharIndex = randomCharIndex;
    }
    result[randomResultLen] = '\0';
    return result;
}

int main()
{
    char* postfix = new char[30];
    for (int i = 0; i < 100; ++i) {
        char* infix = generateRandomSingleDigitExpression(15);
        std::cout << "infix: " << infix << "\n";
        try {
            getPostfixFromInfix(infix, postfix, 30);
            std::cout << "postfix: " << postfix << "\n";
        }
        catch (std::exception& e) {
            std::cout << e.what();
        }
        std::cout << "\n";
    }
    return 0;
}
