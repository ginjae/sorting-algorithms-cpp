#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <cstddef>
#include <vector>

template <typename T, typename Compare>
void max_heapify(std::vector<T>& arr, int n, int i, Compare comp) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest;
    if (left < n && comp(arr[i], arr[left]))    // arr[left] > arr[i]
        largest = left;
    else
        largest = i;
    if (right < n && comp(arr[largest], arr[right]))    // arr[right] > arr[largest]
        largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        max_heapify(arr, n, largest, comp);
    }
}

template <typename T, typename Compare>
void build_max_heap(std::vector<T>& arr, int n, Compare comp) {
    for (int i = n / 2; i >= 0; i--)
        max_heapify(arr, n, i, comp);
}

template <typename T, typename Compare>
void heap_sort(std::vector<T>& arr, Compare comp) {
    int n = arr.size();
    if (n < 2)
        return;
    build_max_heap(arr, n, comp);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        max_heapify(arr, i, 0, comp);
    }
}

#endif