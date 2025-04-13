#ifndef COMB_SORT_H
#define COMB_SORT_H

#include <cstddef>
#include <vector>

#include "bubble_sort.h"

std::vector<int> generate_gaps(int n) {
    std::vector<int> gaps;
    int gap = n / 2;
    while (gap > 0) {
        gaps.push_back(gap);
        gap = gap * 3 / 4;
        if (gap == 1 || gap == 0)
            break;
    }
    return gaps;
}

template <typename T, typename Compare>
void comb_sort(std::vector<T>& arr, int begin, int end, Compare comp) {
    int n = end - begin + 1;
    std::vector<int> gaps = generate_gaps(n);

    for (int l = 0; l < gaps.size(); l++) {
        int inc = gaps[l];
        for (int i = 0; i < n - inc; i++) {
            if (comp(arr[i + inc], arr[i]))     // arr[i] > arr[i + inc]
                std::swap(arr[i], arr[i + inc]);
        }
    }
    
    bubble_sort(arr, begin, end, comp);
}

#endif