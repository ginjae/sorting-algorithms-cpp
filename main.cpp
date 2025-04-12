#include <iostream>
#include "algorithms/bubble_sort.h"
#include "algorithms/heap_sort.h"
#include "algorithms/insertion_sort.h"
#include "algorithms/merge_sort.h"
#include "algorithms/quick_sort.h"
#include "algorithms/selection_sort.h"

using namespace std;

vector<int> ARR = { 5, 2, 4, 6, 1, 3 };
vector<pair<int, char>> PAIR_ARR = {
    {1, 'A'}, {1, 'B'}, {1, 'C'}, {2, 'D'},
    {2, 'E'}, {3, 'F'}, {1, 'G'}, {2, 'H'},
    {2, 'I'}, {1, 'J'}, {2, 'K'}, {2, 'L'},
    {1, 'M'}, {2, 'N'}, {3, 'O'}, {1, 'P'},
    {2, 'Q'}, {3, 'R'}, {3, 'S'}, {1, 'T'}
};
bool pair_comp(const pair<int, char>& a, const pair<int, char>& b) {
    return a.first < b.first;
}

#define SORT_TEST(x) try {  \
        vector<int> arr = ARR;  \
        x(arr, less<int>());    \
        for (auto& a : arr) \
            cout << a << "\t";  \
        cout << endl;   \
        vector<pair<int, char>> pair_arr = PAIR_ARR;    \
        x(pair_arr, pair_comp); \
        for (auto& p : pair_arr)    \
            cout << p.first << ":" << p.second << "\t"; \
        cout << endl;   \
        vector<int> empty_arr;  \
        x(empty_arr, less<int>());  \
    } catch (exception& e) {    \
        cout << e.what() << endl;   \
    }   \
    cout << "↑ " << #x << endl;


int main() {
    SORT_TEST(bubble_sort)
    SORT_TEST(heap_sort)
    SORT_TEST(insertion_sort)
    SORT_TEST(merge_sort)
    SORT_TEST(quick_sort)
    SORT_TEST(selection_sort)

    return 0;
}