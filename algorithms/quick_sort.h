#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <cstddef>
#include <vector>

template <typename T, typename Compare>
size_t partition(std::vector<T>& arr, int left, int right, Compare comp) {
    T x = arr[right];
    int i = left - 1;
    for (int j = left; j <= right - 1; j++) {
        if (!comp(x, arr[j]))   // arr[j] <= x
            std::swap(arr[++i], arr[j]);
    }
    std::swap(arr[i + 1], arr[right]);
    return i + 1;
}

template <typename T, typename Compare>
void quick_sort_rec(std::vector<T>& arr, int left, int right, Compare comp) {
    if (left < right) {
        int mid = partition(arr, left, right, comp);
        quick_sort_rec(arr, left, mid - 1, comp);
        quick_sort_rec(arr, mid + 1, right, comp);
    }
}

template <typename T, typename Compare>
void quick_sort(std::vector<T>& arr, Compare comp) {
    if (arr.size() < 2)
        return;
    quick_sort_rec(arr, 0, arr.size() - 1, comp);
}

#endif