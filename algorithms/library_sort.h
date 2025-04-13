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
    int left = begin;
    int right = end;
    while (left < right) {
        int mid = (left + right) / 2;
        int actual_mid = mid;

        // to find non-gap mid point
        while (actual_mid <= right && !arr[actual_mid].has_value()) actual_mid++;

        // if the right side is all gap
        if (actual_mid >= right) {
            right = mid;
            continue;
        }

        if (comp(value, *arr[actual_mid])) {   // value < arr[actual_mid]
            right = actual_mid;
        } else {
            left = actual_mid + 1;
        }
    }
    int result = left;
    while (result <= end && !arr[result].has_value()) result++;
    if (result > end)
        return left;
    else
        return result;
}

template <typename T, typename Compare>
void insert_with_shift(std::vector<std::optional<T>>& arr, int begin, int end, int idx, T value, Compare comp) {
    int right = idx;
    int left = idx;

    while (right < end && arr[right].has_value())  right++;
    for (int i = right; i > idx; i--)
        arr[i] = arr[i - 1];
    arr[idx] = value;
}

template <typename T, typename Compare>
void library_sort(std::vector<T>& arr, int begin, int end, Compare comp) {
    if (end - begin < 1)
        return;

    int n = end - begin + 1;
    std::vector<std::optional<T>> temp(n * 4, std::nullopt);
    temp[0] = arr[0];

    for (int i = 1; i <= log2(n) + 1; i++) {
        int cur_n = pow(2, i);
        rebalance(temp, begin, cur_n);
        for (int j = cur_n / 2; j < std::min(cur_n, n); j++) {
            int ins = binary_search(temp, arr[j], begin, begin + cur_n * 2 - 1, comp);
            insert_with_shift(temp, begin, begin + cur_n * 2 - 1, ins, arr[j], comp);
        }
    }

    // save answer (to remove gap)
    for (int arr_i = begin, temp_i = 0; arr_i <= end; temp_i++) {
        if (temp[temp_i].has_value())
            arr[arr_i++] = *temp[temp_i];
    }
}

#endif