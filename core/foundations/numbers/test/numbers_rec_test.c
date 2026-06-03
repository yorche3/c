#include <criterion/criterion.h>
#include "../include/numbers.h"

Test(numbers_rec, sum_of_first_n_rec) {
    cr_expect_eq(sum_of_first_n_rec(0), 0, "sum_of_first_n_rec(0) should be 0");
    cr_expect_eq(sum_of_first_n_rec(3), 6, "sum_of_first_n_rec(3) should be 6");
}

Test(numbers_rec, factorial_rec) {
    cr_expect_eq(factorial_rec(0), 1, "factorial_rec(0) should be 1");
    cr_expect_eq(factorial_rec(4), 24, "factorial_rec(4) should be 24");
}

Test(numbers_rec, fibonacci_rec) {
    cr_expect_eq(fibonacci_rec(0), 0, "fibonacci_rec(0) should be 0");
    cr_expect_eq(fibonacci_rec(1), 1, "fibonacci_rec(1) should be 1");
    cr_expect_eq(fibonacci_rec(6), 8, "fibonacci_rec(6) should be 8");
}

Test(numbers_rec, greatest_common_divisor_rec) {
    cr_expect_eq(greatest_common_divisor_rec(12, 8), 4, "greatest_common_divisor_rec(12, 8) should be 4");
    cr_expect_eq(greatest_common_divisor_rec(7, 5), 1, "greatest_common_divisor_rec(7, 5) should be 1");
}

Test(numbers_rec, least_common_multiple_rec) {
    cr_expect_eq(least_common_multiple_rec(4, 6), 12, "least_common_multiple_rec(4, 6) should be 12");
    cr_expect_eq(least_common_multiple_rec(6, 8), 24, "least_common_multiple_rec(6, 8) should be 24");
}