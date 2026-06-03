#include <criterion/criterion.h>
#include "../include/numbers.h"

Test(numbers_ite, sum_of_first_n_iter) {
    cr_expect_eq(sum_of_first_n_iter(0), 0, "sum_of_first_n_iter(0) should be 0");
    cr_expect_eq(sum_of_first_n_iter(3), 6, "sum_of_first_n_iter(3) should be 6");
}

Test(numbers_ite, factorial_iter) {
    cr_expect_eq(factorial_iter(0), 1, "factorial_iter(0) should be 1");
    cr_expect_eq(factorial_iter(4), 24, "factorial_iter(4) should be 24");
}

Test(numbers_ite, fibonacci_iter) {
    cr_expect_eq(fibonacci_iter(0), 0, "fibonacci_iter(0) should be 0");
    cr_expect_eq(fibonacci_iter(1), 1, "fibonacci_iter(1) should be 1");
    cr_expect_eq(fibonacci_iter(6), 8, "fibonacci_iter(6) should be 8");
}

Test(numbers_ite, greatest_common_divisor_iter) {
    cr_expect_eq(greatest_common_divisor_iter(12, 8), 4, "greatest_common_divisor_iter(12, 8) should be 4");
    cr_expect_eq(greatest_common_divisor_iter(7, 5), 1, "greatest_common_divisor_iter(7, 5) should be 1");
}

Test(numbers_ite, least_common_multiple_iter) {
    cr_expect_eq(least_common_multiple_iter(4, 6), 12, "least_common_multiple_iter(4, 6) should be 12");
    cr_expect_eq(least_common_multiple_iter(6, 8), 24, "least_common_multiple_iter(6, 8) should be 24");
}