#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <cstddef>
#include <vector>

template <typename T, typename Compare>
void bubble_sort(std::vector<T>& arr, Compare comp) {
    if (arr.size() < 2)
        return;
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = arr.size() - 1; j > i; j--) {
            if (comp(arr[j], arr[j - 1]))   // arr[j] < arr[j - 1]
                std::swap(arr[j], arr[j - 1]);
        }
    }
}

#endif