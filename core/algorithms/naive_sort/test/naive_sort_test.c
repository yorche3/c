#include <criterion/criterion.h>

#include <string.h>

#include "naive_sort.h"

typedef int *(*sort_fn)(int *, size_t);

/*
 * Fixtures are declared once and reused by the three algorithms. They are
 * const, so every case copies its input into `scratch` before calling the
 * in-place sort and never mutates the shared fixtures.
 */
static const int STANDARD_INPUT[] = {5, 2, 9, 1, 5, 6};
static const int STANDARD_OUTPUT[] = {1, 2, 5, 5, 6, 9};
static const int SORTED_INPUT[] = {1, 2, 3, 4, 5};
static const int REVERSE_INPUT[] = {5, 4, 3, 2, 1};
static const int REVERSE_OUTPUT[] = {1, 2, 3, 4, 5};
static const int EQUAL_INPUT[] = {7, 7, 7, 7};
static const int NEGATIVE_INPUT[] = {3, -1, 4, -5, 0};
static const int NEGATIVE_OUTPUT[] = {-5, -1, 0, 3, 4};
static const int SINGLE_INPUT[] = {42};

#define SCRATCH_CAPACITY 6
static int scratch[SCRATCH_CAPACITY];

#define ARRAY_LEN(a) (sizeof(a) / sizeof *(a))

static void run_case(sort_fn sort, const char *algorithm, const char *case_name,
                     const int *input, const int *expected, size_t n)
{
    memcpy(scratch, input, n * sizeof *scratch);
    int *result = sort(scratch, n);

    cr_expect_eq(result, scratch,
                 "%s: %s: should return the array sorted in place",
                 algorithm, case_name);
    cr_expect_arr_eq(result, expected, n * sizeof *result,
                     "%s: %s: unexpected sorted output", algorithm, case_name);
}

/* Runs the 8 shared cases against any sort function. */
static void assert_all_cases(sort_fn sort, const char *algorithm)
{
    run_case(sort, algorithm, "unsorted",
             STANDARD_INPUT, STANDARD_OUTPUT, ARRAY_LEN(STANDARD_INPUT));
    run_case(sort, algorithm, "already sorted",
             SORTED_INPUT, SORTED_INPUT, ARRAY_LEN(SORTED_INPUT));
    run_case(sort, algorithm, "reverse order",
             REVERSE_INPUT, REVERSE_OUTPUT, ARRAY_LEN(REVERSE_INPUT));
    run_case(sort, algorithm, "equal elements",
             EQUAL_INPUT, EQUAL_INPUT, ARRAY_LEN(EQUAL_INPUT));
    run_case(sort, algorithm, "negative values",
             NEGATIVE_INPUT, NEGATIVE_OUTPUT, ARRAY_LEN(NEGATIVE_INPUT));
    run_case(sort, algorithm, "single element",
             SINGLE_INPUT, SINGLE_INPUT, ARRAY_LEN(SINGLE_INPUT));

    /* Empty array: returned unchanged, same pointer. */
    cr_expect_eq(sort(scratch, 0), scratch,
                 "%s: empty: should return the same empty array", algorithm);

    /* NULL array: the failure indicator. */
    cr_expect_eq(sort(NULL, 5), NULL,
                 "%s: null: should return the NULL failure indicator",
                 algorithm);
}

Test(naive_sort, selection_sort)
{
    assert_all_cases(selection_sort, "selection_sort");
}

Test(naive_sort, bubble_sort)
{
    assert_all_cases(bubble_sort, "bubble_sort");
}

Test(naive_sort, insertion_sort)
{
    assert_all_cases(insertion_sort, "insertion_sort");
}
