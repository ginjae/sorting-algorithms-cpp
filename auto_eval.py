import subprocess
import time
import psutil
import sys
import os

SORTING_ALGORITHMS = [
    "bubble_sort", "cocktail_shaker_sort", "comb_sort", "heap_sort",
    "insertion_sort", "intro_sort", "library_sort", "merge_sort",
    "quick_sort", "selection_sort", "tim_sort", "tournament_sort"
]

DATASET_TYPES = [
    "random",
    "dense_random",
    "ascending",
    "descending",
    "partially_sorted"
]

DATASET_SIZES = [
    "1000",
    "10000",
    "100000",
    "200000",
    "400000",
    "600000",
    "800000",
    "1000000"
]

# DATASET_SIZES = [
#     "200000",
#     "300000",
#     "400000",
#     "500000",
#     "600000",
#     "700000",
#     "800000",
#     "900000"
# ]

def evaluation(sorting_algorithm: str, dataset_path: str, iterations: str):
    cmd = ["./eval", sorting_algorithm, dataset_path, iterations]

    process = subprocess.Popen(cmd, stdout=subprocess.PIPE)
    pid = process.pid
    p = psutil.Process(pid)

    peak_memory = 0
    try:
        while process.poll() is None:
            mem = p.memory_info().rss
            peak_memory = max(peak_memory, mem)
            time.sleep(0.01)
    except psutil.NoSuchProcess:
        pass

    stdout, _ = process.communicate()

    return peak_memory, stdout.decode()

def write_and_print(file, string):
    file.write(string)
    # print(string, end="")

if __name__ == "__main__":
    subprocess.run(["make", "eval"])

    sorting_algorithm = sys.argv[1]
    if sorting_algorithm not in SORTING_ALGORITHMS:
        print("Usage: python3 auto_eval.py <sorting algorithm>")
        quit()

    mems = []
    times = []
    print(sorting_algorithm)

    os.makedirs("results/" + sorting_algorithm, exist_ok=True)
    with open("results/" + sorting_algorithm + ".txt", mode="w") as f:
        write_and_print(f, f"Algorithm               : {sorting_algorithm}\n")
        _, output = evaluation(sorting_algorithm, "stability", "1")
        write_and_print(f, output.strip())
        write_and_print(f, "\n")
        
        for dataset_type in DATASET_TYPES:
            temp_mem = []
            temp_time = []
            for dataset_size in DATASET_SIZES:
                dataset_path = "datasets/" + dataset_type + "_" + \
                    dataset_size + ".txt"
                iterations = "10"
                # iterations = "12"
                # if dataset_size == "1000000":
                #     if sorting_algorithm == "bubble_sort" or sorting_algorithm == "cocktail_shaker_sort" \
                #     or sorting_algorithm == "insertion_sort" or sorting_algorithm == "selection_sort":
                #         iterations = "3"

                mem, output = evaluation(sorting_algorithm, dataset_path, iterations)
                running_times = list(map(float, output.strip().split("\n")))

                temp_mem.append(mem)
                temp_time.append(sum(running_times) / len(running_times))

                write_and_print(f, f"Dataset                 : {dataset_path}\n")
                write_and_print(f, f"Peak Memory             : {mem} bytes\n")
                write_and_print(f, f"Average Running Time    : {sum(running_times) / len(running_times)} sec\n")
                write_and_print(f, "Raw Data:\n")
                for running_time in running_times:
                    write_and_print(f, f"{running_time}\n")
                write_and_print(f, "=" * 64 + "\n")
            mems.append(temp_mem)
            times.append(temp_time)
            print("[peak memory]")
            print(mems)
            # for m in mems:
            #     print(m, end=",")
            # print()
            print("[running time]")
            print(times)
            # for t in times:
            #     print(t, end=",")
            # print()

