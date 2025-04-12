#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <cstddef>
#include <vector>

template <typename T, typename Compare>
void selection_sort(std::vector<T>& arr, int begin, int end, Compare comp) {
    if (end - begin < 1)
        return;
    for (int i = begin; i < end; i++) {
        int smallest = i;
        for (int j = i + 1; j < end + 1; j++)
            if (comp(arr[j], arr[smallest]))    // arr[j] < arr[smallest]
                smallest = j;
        std::swap(arr[i], arr[smallest]);
    }
}

#endif