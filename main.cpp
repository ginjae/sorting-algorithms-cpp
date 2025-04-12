#include <iostream>
#include "algorithms/bubble_sort.h"
#include "algorithms/heap_sort.h"
#include "algorithms/insertion_sort.h"
#include "algorithms/merge_sort.h"
#include "algorithms/quick_sort.h"
#include "algorithms/selection_sort.h"
#include "algorithms/cocktail_shaker_sort.h"
#include "algorithms/intro_sort.h"

using namespace std;

vector<int> ARR = { 5, 2, 4, 6, 1, 3 };
vector<pair<int, char>> PAIR_ARR = {
    {1, 'S'}, {1, 't'}, {1, 'a'}, {2, 'r'},
    {2, 't'}, {3, 'o'}, {1, 'b'}, {2, 'i'},
    {2, 'n'}, {1, 'l'}, {2, 'g'}, {2, 'A'},
    {1, 'e'}, {2, 'l'}, {3, 'r'}, {1, 'S'},
    {2, 'g'}, {3, 'i'}, {3, 't'}, {1, 'o'},
    {4, 'm'}, {3, 'h'}
};
bool pair_comp(const pair<int, char>& a, const pair<int, char>& b) {
    return a.first < b.first;
}

#define SORT_TEST(x) try {  \
        vector<int> arr = ARR;  \
        x(arr, 0, arr.size() - 1, less<int>()); \
        for (auto& a : arr) \
            cout << a << " ";   \
        cout << endl;   \
        vector<pair<int, char>> pair_arr = PAIR_ARR;    \
        x(pair_arr, 0, pair_arr.size() - 1, pair_comp); \
        for (auto& p : pair_arr)    \
            cout << p.second;   \
        cout << endl;   \
        vector<int> empty_arr;  \
        x(empty_arr, 0, empty_arr.size() - 1, less<int>()); \
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
    SORT_TEST(cocktail_shaker_sort)
    SORT_TEST(intro_sort)

    return 0;
}