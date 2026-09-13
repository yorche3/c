#include "naive_sort.h"

#include <stdbool.h>

// Selection sort: sorts an integer array using the selection sort algorithm
// input: arr - pointer to the array to be sorted, n - number of elements in the array
// output: pointer to the sorted array (same as input) or NULL if input is NULL
int *selection_sort(int *arr, size_t n)
{
    if (arr == NULL) {
        return NULL;
    }
    if (n <= 1) {
        return arr;
    }

    for (size_t i = 0; i < n - 1; i++) {
        size_t min_idx = i;

        for (size_t j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }

    return arr;
}

// Bubble sort: sorts an integer array using the bubble sort algorithm
// input: arr - pointer to the array to be sorted, n - number of elements in the array
// output: pointer to the sorted array (same as input) or NULL if input is NULL
int *bubble_sort(int *arr, size_t n)
{
    if (arr == NULL) {
        return NULL;
    }
    if (n <= 1) {
        return arr;
    }

    for (size_t i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (size_t j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }

    return arr;
}

// Insertion sort: sorts an integer array using the insertion sort algorithm
// input: arr - pointer to the array to be sorted, n - number of elements in the array
// output: pointer to the sorted array (same as input) or NULL if input is NULL
int *insertion_sort(int *arr, size_t n)
{
    if (arr == NULL) {
        return NULL;
    }
    if (n <= 1) {
        return arr;
    }

    for (size_t i = 1; i < n; i++) {
        const int key = arr[i];
        size_t j = i;

        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }

    return arr;
}
