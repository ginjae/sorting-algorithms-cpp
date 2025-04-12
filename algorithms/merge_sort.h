#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <cstddef>
#include <vector>

template <typename T, typename Compare>
void merge(std::vector<T>& arr, int left, int mid, int right, Compare comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<T> a1(n1), a2(n2);
    for (int i = 0; i < n1; i++)
        a1[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        a2[i] = arr[mid + i + 1];

    // will not use sentinel value
    int i = left, i1 = 0, i2 = 0;
    while (i1 < n1 && i2 < n2) {
        if (!comp(a2[i2], a1[i1]))  // a1[i1] <= a2[i2]
            arr[i++] = a1[i1++];
        else
            arr[i++] = a2[i2++];
    }

    while (i1 < n1)
        arr[i++] = a1[i1++];
    while (i2 < n2)
        arr[i++] = a2[i2++];
}

template <typename T, typename Compare>
void merge_sort_rec(std::vector<T>& arr, int left, int right, Compare comp) {
    if (left < right) {
        int mid = (right + left) / 2;
        merge_sort_rec(arr, left, mid, comp);
        merge_sort_rec(arr, mid + 1, right, comp);
        merge(arr, left, mid, right, comp);
    }
}

template <typename T, typename Compare>
void merge_sort(std::vector<T>& arr, Compare comp) {
    if (arr.size() < 2)
        return;
    merge_sort_rec(arr, 0, arr.size() - 1, comp);
}

#endif