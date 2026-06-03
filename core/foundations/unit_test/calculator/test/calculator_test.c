#include <criterion/criterion.h>
#include "../include/calculator.h"

Test(calculator, addition) {
    cr_expect_eq(addition(2, 3), 5);
    cr_expect_eq(addition(-1, 1), 0);
    cr_expect_eq(addition(0, 0), 0);
}

Test(calculator, subtraction) {
    cr_expect_eq(subtraction(5, 2), 3);
    cr_expect_eq(subtraction(0, 0), 0);
    cr_expect_eq(subtraction(-1, -1), 0);
}

Test(calculator, multiplication) {
    cr_expect_eq(multiplication(3, 4), 12);
    cr_expect_eq(multiplication(0, 5), 0);
    cr_expect_eq(multiplication(5, 0), 0);
}

Test(calculator, division) {
    cr_expect_eq(division(10, 3), 3);
    cr_expect_eq(division(0, 5), 0);
    cr_expect_eq(division(5, 1), 5);
}

Test(calculator, modulus) {
    cr_expect_eq(modulus(10, 3), 1);
    cr_expect_eq(modulus(0, 5), 0);
    cr_expect_eq(modulus(5, 5), 0);
}
