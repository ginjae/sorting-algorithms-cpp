#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>
#include <algorithm>
#include <sys/resource.h>

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

size_t getCurrentRSS() {
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    return r_usage.ru_maxrss * 1024; // kilobytes to bytes
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
    {1, 'S'}, {1, 't'}, {1, 'a'}, {2, 'r'},
    {2, 't'}, {3, 'o'}, {1, 'b'}, {2, 'i'},
    {2, 'n'}, {1, 'l'}, {2, 'g'}, {2, 'A'},
    {1, 'e'}, {2, 'l'}, {3, 'r'}, {1, 'S'},
    {2, 'g'}, {3, 'i'}, {3, 't'}, {1, 'o'},
    {4, 'm'}, {3, 'h'}
};

/* To check stability in sorting algorithms */
bool pair_comp(const pair<int, char>& a, const pair<int, char>& b) {
    return a.first < b.first;
}

template <typename T>
using SortFunc = function<void(vector<T>&, int, int, function<bool(const T&, const T&)>)>;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: eval <sorting algorithm> <dataset path> <iterations>\n";
        return 0;
    }
    string sorting = argv[1];
    string dataset = argv[2];
    int iterations;
    try {
        iterations = stoi(argv[3]);
    } catch (exception& e) {
        cout << "Usage: eval <sorting algorithm> <dataset path> <iterations>\n";
        return 0;
    }

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
        stable_sort(stable_answer.begin(), stable_answer.end(), pair_comp);
        sort_pair(pair_arr, 0, pair_arr.size() - 1, pair_comp);
        bool is_stable = true;
        cout << "(stability test result: ";
        // cout << "stable\t" << sorting << endl;
        for (size_t i = 0; i < pair_arr.size(); i++) {
            // cout << stable_answer[i].first << ", " << stable_answer[i].second << "\t"    \
            //     << pair_arr[i].first << ", " << pair_arr[i].second << endl;
            cout << pair_arr[i].second;
            if (pair_arr[i] != stable_answer[i])
                is_stable = false;
        }
        if (is_stable)
            cout << " -> " << sorting + " is stable)" << endl;
        else
            cout << " -> " << sorting + " is not stable)" << endl;
        return 0;
    }

    vector<int> arr;
    load_dataset(arr, dataset);
    for (int i = 0; i < iterations; i++) {
        vector<int> temp = arr;
        // int before = getCurrentRSS();
        auto start = chrono::system_clock::now();
        sort_int(temp, 0, temp.size() - 1, less<int>());
        chrono::duration<double> sec = chrono::system_clock::now() - start;
        // int after = getCurrentRSS();
        // cout << before << " - " << after << endl;
        // cout << "MEM: " << after - before << " bytes\n";
        cout << fixed;
        cout.precision(9);
        cout << sec.count() << endl;
        if (i == 0) {
            ofstream outfile("results/" + sorting + "/" + dataset.substr(8, dataset.size()));
            for (int n : temp)
                outfile << n << endl;
            outfile.close();
        }
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