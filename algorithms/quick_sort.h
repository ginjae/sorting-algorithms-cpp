#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <cstddef>
#include <vector>

template <typename T, typename Compare>
size_t partition(std::vector<T>& arr, int begin, int end, int pivot_index, Compare comp) {
    std::swap(arr[pivot_index], arr[end]);
    T x = arr[end];
    int i = begin - 1;
    for (int j = begin; j <= end - 1; j++) {
        if (!comp(x, arr[j]))   // arr[j] <= x
            std::swap(arr[++i], arr[j]);
    }
    std::swap(arr[i + 1], arr[end]);
    return i + 1;
}

template <typename T, typename Compare>
void quick_sort_rec(std::vector<T>& arr, int begin, int end, Compare comp) {
    if (begin < end) {
        int pivot_index = begin + rand() % (end - begin + 1);   // select the random element as a pivot
        pivot_index = partition(arr, begin, end, pivot_index, comp);
        quick_sort_rec(arr, begin, pivot_index - 1, comp);
        quick_sort_rec(arr, pivot_index + 1, end, comp);
    }
}

template <typename T, typename Compare>
void quick_sort(std::vector<T>& arr, int begin, int end, Compare comp) {
    if (end - begin < 1)
        return;
    quick_sort_rec(arr, begin, end, comp);
}

#endif