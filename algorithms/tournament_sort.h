#ifndef TOURNAMENT_SORT_H
#define TOURNAMENT_SORT_H

#include <cstddef>
#include <vector>
#include <optional>

template <typename T, typename Compare>
void tournament_sort(std::vector<T>& arr, int begin, int end, Compare comp) {
    // construct complete binary tree 
    int tree_size = 1;
    int n = end - begin + 1;
    while (tree_size <= n)
        tree_size *= 2;
    tree_size *= 2;
    std::vector<std::optional<T>> tree(tree_size, std::nullopt);

    // leaf node initialization with arr
    for (int i = 0; i < n; i++)
        tree[tree_size / 2 + i] = arr[begin + i];

    // internal node initialization with the smaller value of two children
    for (int i = tree_size / 2 - 1; i >= 1; i--) {
        auto& left = tree[2 * i];
        auto& right = tree[2 * i + 1];
        if (left.has_value() && right.has_value())
            tree[i] = comp(*left, *right) ? left : right;
        else
            tree[i] = left.has_value() ? left : right;
    }

    while (begin < n) {
        arr[begin++] = *tree[1];
        tree[1] = std::nullopt;
        int node = 1;

        // remove the smaller value while going down the tree
        while (node < tree_size / 2) {
            int left = 2 * node;
            int right = 2 * node + 1;

            if (tree[left].has_value() && tree[right].has_value())
                node = comp(*tree[left], *tree[right]) ? left : right;
            else
                node = tree[left].has_value() ? left : right;

            tree[node] = std::nullopt;
        }

        // re-construct the tree along the path up to the root
        while (node > 1) {
            node /= 2;
            auto& left = tree[2 * node];
            auto& right = tree[2 * node + 1];

            if (left.has_value() && right.has_value())
                tree[node] = comp(*left, *right) ? left : right;
            else
                tree[node] = left.has_value() ? left : right;
        }
    }

}

#endif