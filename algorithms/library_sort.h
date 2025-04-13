#ifndef LIBRARY_SORT_H
#define LIBRARY_SORT_H

#include <cstddef>
#include <vector>
#include <optional>
#include <cmath>

template <typename T>
void rebalance(std::vector<std::optional<T>>& arr, int begin, int n) {
    for (int read_idx = begin + n - 1, write_idx = begin + n * 2 - 2; read_idx > begin; read_idx--) {
        arr[write_idx] = arr[read_idx];
        arr[write_idx - 1] = std::nullopt;
        write_idx -= 2;
    }
}

template <typename T, typename Compare>
int binary_search(std::vector<std::optional<T>>& arr, T value, int begin, int end, Compare comp) {
    while (begin < end) {
        int mid = (begin + end) / 2;
        int actual_mid = mid;

        // to find non-gap mid point
        while (actual_mid < end && !arr[actual_mid].has_value()) actual_mid++;

        // if the right side is all gap
        if (actual_mid == end) {
            end = mid;
            continue;
        }

        if (!comp(*arr[actual_mid], value)) {   // arr[actual_mid] >= value
            end = actual_mid;
        } else {
            begin = actual_mid + 1;
        }
    }

    return begin;

    /* linear search for test */
    // while (1) {
    //     if (begin >= end)
    //         return end;
    //     if (!arr[begin].has_value())
    //         begin++;
    //     else {
    //         if (!comp(*arr[begin], value))
    //             return begin;
    //         else
    //             begin++;
    //     }
    // }
}

template <typename T>
void insert_with_shift(std::vector<std::optional<T>>& arr, int begin, int end, int idx, T value) {
    if (!arr[idx].has_value()) {
        arr[idx] = value;
        return;
    }

    int right = idx;
    int left = idx;

    while (right <= end && arr[right].has_value())  right++;

    if (right > end) {
        while (left >= begin && arr[left].has_value())  left--;
        for (int i = left; i < idx; i++)
            arr[i] = arr[i + 1];
        arr[idx] = value;
    } else {
        for (int i = right; i > idx; i--)
            arr[i] = arr[i - 1];
        arr[idx] = value;
    }
}

template <typename T, typename Compare>
void library_sort(std::vector<T>& arr, int begin, int end, Compare comp) {
    if (end - begin < 1)
        return;

    int n = end - begin + 1;
    std::vector<std::optional<T>> temp(n * 2, std::nullopt);

    // start with two elements
    if (!comp(arr[1], arr[0])) {
        temp[0] = arr[0];
        temp[1] = arr[1];
    } else {
        temp[0] = arr[1];
        temp[1] = arr[0];
    }

    // 4 elements in the first iter, 8 elements in the second iter, ...
    for (int i = 1; i <= log2(n); i++) {
        int cur_n = pow(2, i);
        rebalance(temp, begin, cur_n);
        for (int j = cur_n; j < std::min(cur_n * 2, n); j++) {
            int ins = binary_search(temp, arr[j], begin, begin + cur_n * 2 - 1, comp);
            insert_with_shift(temp, begin, begin + cur_n * 2 - 1, ins, arr[j]);
        }
    }

    // save answer (to remove gap)
    for (int arr_i = begin, temp_i = 0; arr_i <= end; temp_i++) {
        if (temp[temp_i].has_value())
            arr[arr_i++] = *temp[temp_i];
    }
}

#endif