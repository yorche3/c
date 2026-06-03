#include "../include/calculator.h"

int addition(int a, int b) {
    return a + b;
}

int subtraction(int a, int b) {
    return a - b;
}

int multiplication(int a, int b) {
    int product = 0;
    for (int i = 0; i < b; i++) {
        product = addition(product, a);
    }
    return product;
}

int division(int a, int b) {
    int quotient = 0;
    while (a >= b) {
        a -= b;
        quotient++;
    }
    return quotient;
}

int modulus(int a, int b) {
    return subtraction(a, multiplication(b, division(a, b)));
}
