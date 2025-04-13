#ifndef TIM_SORT_H
#define TIM_SORT_H

#include <cstddef>
#include <vector>

#include "insertion_sort.h"
#include "merge_sort.h"

template <typename T, typename Compare>
void tim_sort(std::vector<T>& arr, int begin, int end, Compare comp) {
    int n = end - begin + 1;
    int run = 32;
    int i = begin;
    int left = begin;
    int size = run;

    while (i < end) {
        int tmp = std::min(i + run - 1, n - 1);
        insertion_sort(arr, i, tmp, comp);
        i = i + run;
    }

    while (size < n) {
        while (left < n) {
            int mid = left + size - 1;
            int right = std::min(left + 2 * size - 1, n - 1);
            if (mid < right)
                merge(arr, left, mid, right, comp);
            left = left + 2 * size;
        }
        left = 0;
        size = size * 2;
    }
}

#endif