#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <cstddef>
#include <vector>

template <typename T, typename Compare>
void bubble_sort(std::vector<T>& arr, int begin, int end, Compare comp) {
    if (end - begin < 1)
        return;
    for (int i = begin; i < end; i++) {
        for (int j = end; j > i; j--) {
            if (comp(arr[j], arr[j - 1]))   // arr[j] < arr[j - 1]
                std::swap(arr[j], arr[j - 1]);
        }
    }
}

#endif