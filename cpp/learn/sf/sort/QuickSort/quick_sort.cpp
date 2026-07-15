#include <iostream>
#include <vector>
#include <algorithm>

static int partition(std::vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low]) std::swap(arr[low], arr[mid]);
    if (arr[high] < arr[low]) std::swap(arr[low], arr[high]);
    if (arr[mid] < arr[high]) std::swap(arr[mid], arr[high]);
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

static void quick_sort_inplace(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_inplace(arr, low, pi - 1);
        quick_sort_inplace(arr, pi + 1, high);
    }
}

std::vector<int> quick_sort(std::vector<int> arr) {
    if (arr.size() <= 1) return arr;
    quick_sort_inplace(arr, 0, arr.size() - 1);
    return arr;
}

int main(int argc, char* argv[]) {
    std::vector<int> arr;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i)
            arr.push_back(std::stoi(argv[i]));
    } else {
        arr = {3, 6, 8, 10, 1, 2, 1};
    }

    std::cout << "原始数组:";
    for (int x : arr) std::cout << " " << x;
    std::cout << std::endl;

    std::vector<int> sorted = quick_sort(std::move(arr));

    std::cout << "排序结果:";
    for (int x : sorted) std::cout << " " << x;
    std::cout << std::endl;

    return 0;
}
