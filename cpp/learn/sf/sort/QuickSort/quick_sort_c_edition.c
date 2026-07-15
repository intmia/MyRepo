#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int main(int argc, char *argv[]) {
    int *arr;
    int n;

    if (argc > 1) {
        n = argc - 1;
        arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL) {
            fprintf(stderr, "内存分配失败\n");
            return 1;
        }
        for (int i = 1; i < argc; i++) {
            arr[i - 1] = atoi(argv[i]);
        }
    } else {
        int default_arr[] = {3, 6, 8, 10, 1, 2, 1};
        n = sizeof(default_arr) / sizeof(default_arr[0]);
        arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL) {
            fprintf(stderr, "内存分配失败\n");
            return 1;
        }
        for (int i = 0; i < n; i++) {
            arr[i] = default_arr[i];
        }
    }

    printf("原始数组:");
    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    quick_sort(arr, 0, n - 1);

    printf("排序结果:");
    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}