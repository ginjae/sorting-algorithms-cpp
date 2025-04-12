#ifndef INTRO_SORT_H
#define INTRO_SORT_H

#include <cstddef>
#include <vector>
#include <cmath>

#include "insertion_sort.h"
#include "heap_sort.h"
#include "quick_sort.h"

const int size_threshold = 16;

template <typename T, typename Compare>
int median_of_3(std::vector<T>& arr, int i, int j, int k, Compare comp) {
    if (comp(arr[i], arr[j]) ^ comp(arr[i], arr[k]))
        return i;
    else if (comp(arr[j], arr[i]) ^ comp(arr[j], arr[k]))
        return j;
    return k;
}

template <typename T, typename Compare>
void intro_sort_rec(std::vector<T>& arr, int begin, int end, int depth_limit, Compare comp) {
    while (end - begin > size_threshold) {
        if (depth_limit == 0) {
            heap_sort(arr, begin, end, comp);
            return;
        }
        int pivot_index = median_of_3(arr, begin, begin + (end - begin) / 2, end - 1, comp);
        pivot_index = partition(arr, begin, end, pivot_index, comp);
        intro_sort_rec(arr, pivot_index, end, depth_limit - 1, comp);
        end = pivot_index;
    }
}

template <typename T, typename Compare>
void intro_sort(std::vector<T>& arr, int begin, int end, Compare comp) {
    if (end - begin < 1)
        return;
    int depth_limit = 2 * log2(end - begin);
    intro_sort_rec(arr, begin, end, depth_limit, comp);
    insertion_sort(arr, begin, end, comp);
}

#endif