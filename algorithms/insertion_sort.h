#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <cstddef>
#include <vector>

template <typename T, typename Compare>
void insertion_sort(std::vector<T>& arr, Compare comp) {
    for (int j = 1; j < arr.size(); j++) {
        T key = arr[j];
        int i = j - 1;
        while (i >= 0 && comp(key, arr[i])) {   // arr[i] < key
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}

#endif