#include <../include/numbers.h>

int sum_of_first_n_rec(int n) {
    if (n == 0) {
        return 0;
    }
    return n + sum_of_first_n_rec(n - 1);
}

int factorial_rec(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial_rec(n - 1);
}

int fibonacci_rec(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_rec(n - 1) + fibonacci_rec(n - 2);
}

int greatest_common_divisor_rec(int a, int b) {
    if (b == 0) {
        return a;
    }
    return greatest_common_divisor_rec(b, a % b);
}

int least_common_multiple_rec(int a, int b) {
    return (a * b) / greatest_common_divisor_rec(a, b);
}

static int sum_of_first_n_acc_help(int n, int acc) {
    if (n == 0) {
        return acc;
    }
    return sum_of_first_n_acc_help(n - 1, acc + n);
}

int sum_of_first_n_acc(int n) {
    return sum_of_first_n_acc_help(n, 0);
}

static int factorial_acc_help(int n, int acc) {
    if (n == 0) {
        return acc;
    }
    return factorial_acc_help(n - 1, acc * n);
}

int factorial_acc(int n) {
    return factorial_acc_help(n, 1);
}

static int fibonacci_acc_help(int n, int a, int b) {
    if (n == 0) {
        return a;
    }
    return fibonacci_acc_help(n - 1, b, a + b);
}

int fibonacci_acc(int n) {
    return fibonacci_acc_help(n, 0, 1);
}

static int greatest_common_divisor_acc_help(int a, int b) {
    if (b == 0) {
        return a;
    }
    return greatest_common_divisor_acc_help(b, a % b);
}

int greatest_common_divisor_acc(int a, int b) {
    return greatest_common_divisor_acc_help(a, b);
}

int least_common_multiple_acc(int a, int b) {
    return (a * b) / greatest_common_divisor_acc(a, b);
}

int sum_of_first_n_iter(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int factorial_iter(int n) {
    int fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int fibonacci_iter(int n) {
    if (n <= 1) {
        return n;
    }
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int greatest_common_divisor_iter(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int least_common_multiple_iter(int a, int b) {
    return (a * b) / greatest_common_divisor_iter(a, b);
}