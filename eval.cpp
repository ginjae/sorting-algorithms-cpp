#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>
#include <algorithm>

#include "algorithms/bubble_sort.h"
#include "algorithms/heap_sort.h"
#include "algorithms/insertion_sort.h"
#include "algorithms/merge_sort.h"
#include "algorithms/quick_sort.h"
#include "algorithms/selection_sort.h"
#include "algorithms/cocktail_shaker_sort.h"
#include "algorithms/intro_sort.h"
#include "algorithms/tim_sort.h"
#include "algorithms/comb_sort.h"
#include "algorithms/library_sort.h"
#include "algorithms/tournament_sort.h"

using namespace std;

void load_dataset(vector<int>& arr, string file_path) {
    arr.clear();
    ifstream file(file_path);
    string line;
    while (getline(file, line)) {
        arr.push_back(stoi(line));
    }
    file.close();
}

/*
string dataset_types[] = {
    "random",
    "dense_random",
    "ascending",
    "descending",
    "partially_sorted"
};

string dataset_sizes[] = {
    "1000",
    "10000",
    "100000",
    "1000000"
};
*/

/* To check stability in sorting algorithms */
vector<pair<int, char>> pair_arr = {
    {3, 'A'}, {2, 'B'}, {1, 'C'}, {2, 'D'},
    {2, 'E'}, {3, 'F'}, {1, 'G'}, {2, 'H'},
    {2, 'I'}, {1, 'J'}, {2, 'K'}, {2, 'L'},
    {1, 'M'}, {2, 'N'}, {3, 'O'}, {1, 'P'},
    {2, 'Q'}, {3, 'R'}, {3, 'S'}, {1, 'T'}
};

/* To check stability in sorting algorithms */
bool pair_comp(const pair<int, char>& a, const pair<int, char>& b) {
    return a.first < b.first;
}

template <typename T>
using SortFunc = function<void(vector<T>&, int, int, function<bool(const T&, const T&)>)>;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: eval <sorting algorithm> <dataset path>\n";
        return 0;
    }
    string sorting = argv[1];
    string dataset = argv[2];

    SortFunc<int> sort_int;
    SortFunc<pair<int, char>> sort_pair;
    
#define SET_SORT_FUNCTION(NAME) \
    else if (sorting == #NAME) { \
        sort_int = NAME<int, function<bool(const int&, const int&)>>; \
        sort_pair = NAME<pair<int, char>, function<bool(const pair<int, char>&, const pair<int, char>&)>>; \
    }
    
    if (false) {}
    SET_SORT_FUNCTION(bubble_sort)
    SET_SORT_FUNCTION(heap_sort)
    SET_SORT_FUNCTION(insertion_sort)
    SET_SORT_FUNCTION(merge_sort)
    SET_SORT_FUNCTION(quick_sort)
    SET_SORT_FUNCTION(selection_sort)
    SET_SORT_FUNCTION(cocktail_shaker_sort)
    SET_SORT_FUNCTION(intro_sort)
    SET_SORT_FUNCTION(tim_sort)
    SET_SORT_FUNCTION(comb_sort)
    SET_SORT_FUNCTION(library_sort)
    SET_SORT_FUNCTION(tournament_sort)
    else {
        cout << "Invalid sorting algorithm" << endl;
        return 0;
    }

    if (dataset == "stability") {
        auto stable_answer = pair_arr;
        stable_sort(stable_answer.begin(), stable_answer.end());
        sort_pair(pair_arr, 0, pair_arr.size() - 1, pair_comp);
        bool is_stable = true;
        cout << "stable\t" << sorting << endl;
        for (size_t i = 0; i < pair_arr.size(); i++) {
            cout << stable_answer[i].first << ", " << stable_answer[i].second << "\t"    \
                << pair_arr[i].first << ", " << pair_arr[i].second << endl;
            if (pair_arr[i] != stable_answer[i])
                is_stable = false;
        }
        if (is_stable)
            cout << sorting + " is stable" << endl;
        else
            cout << sorting + " is not stable" << endl;
        return 0;
    }

    cout << "Evaluating " << sorting << ":" << endl;
    vector<int> arr;
    load_dataset(arr, dataset);
    for (int i = 0; i < 12; i++) {
        vector<int> temp = arr;
        auto start = chrono::system_clock::now();
        sort_int(temp, 0, temp.size() - 1, less<int>());
        chrono::duration<double> sec = chrono::system_clock::now() - start;
        cout << sec.count() << endl;
    }

    /*
    for (string dataset_type : dataset_types) {
        for (string dataset_size : dataset_sizes) {
            string dataset_name = dataset_type + "_" + dataset_size + ".txt";
            load_dataset(arr, "datasets/" + dataset_name);
            cout << dataset_name << endl;
            for (int i = 0; i < 12; i++) {
                vector<int> temp = arr;
                auto start = chrono::system_clock::now();
                sort_int(temp, less<int>());
                chrono::duration<double> sec = chrono::system_clock::now() - start;
                // if (i == 0) {
                //     ofstream outfile("results/" + arg + "/" + dataset_name);
                //     for (int n : temp)
                //         outfile << n << endl;
                //     outfile.close();
                // }
                cout << sec.count() << endl;
            }
        }
    }
    */

    return 0;
}