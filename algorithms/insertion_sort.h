#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <cstddef>
#include <vector>

template <typename T, typename Compare>
void insertion_sort(std::vector<T>& arr, int begin, int end, Compare comp) {
    for (int j = begin + 1; j <= end; j++) {
        T key = arr[j];
        int i = j - 1;
        while (i >= begin && comp(key, arr[i])) {   // arr[i] < key
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}

#endif