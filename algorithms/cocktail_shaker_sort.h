#ifndef COCKTAIL_SHAKER_SORT_H
#define COCKTAIL_SHAKER_SORT_H

#include <cstddef>
#include <vector>

template <typename T, typename Compare>
void cocktail_shaker_sort(std::vector<T>& arr, int begin, int end, Compare comp) {
    end--;
    while (begin <= end) {
        int new_begin = end;
        int new_end = begin;
        for (int i = begin; i <= end; i++) {
            if (comp(arr[i + 1], arr[i])) {     // arr[i] > arr[i + 1]
                std::swap(arr[i], arr[i + 1]);
                new_end = i;
            }
        }

        end = new_end - 1;

        for (int i = end; i >= begin; i--) {
            if (comp(arr[i + 1], arr[i])) {     // arr[i] > arr[i + 1]
                std::swap(arr[i], arr[i + 1]);
                new_begin = i;
            }
        }

        begin = new_begin + 1;
    }
}

#endif