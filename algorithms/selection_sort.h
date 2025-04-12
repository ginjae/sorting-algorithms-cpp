#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <cstddef>
#include <vector>

template <typename T, typename Compare>
void selection_sort(std::vector<T>& arr, Compare comp) {
    if (arr.size() < 2)
        return;
    for (int i = 0; i < arr.size() - 1; i++) {
        int smallest = i;
        for (int j = i + 1; j < arr.size(); j++)
            if (comp(arr[j], arr[smallest]))    // arr[j] < arr[smallest]
                smallest = j;
        std::swap(arr[i], arr[smallest]);
    }
}

#endif