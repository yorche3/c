#include <criterion/criterion.h>
#include "../include/calculator.h"

Test(calculator, addition) {
    cr_expect_eq(addition(2, 3), 5, "2 + 3 should equal 5");
}

Test(calculator, subtraction) {
    cr_expect_eq(subtraction(5, 2), 3, "5 - 2 should equal 3");
}

Test(calculator, multiplication) {
    cr_expect_eq(multiplication(3, 4), 12, "3 * 4 should equal 12");
}

Test(calculator, division) {
    cr_expect_eq(division(10, 3), 3, "10 / 3 should equal 3");
}

Test(calculator, modulus) {
    cr_expect_eq(modulus(10, 3), 1, "10 % 3 should equal 1");
}
