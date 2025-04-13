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
    "1000000"
]

def evaluation(sorting_algorithm: str, dataset_path: str):
    cmd = ["./eval", sorting_algorithm, dataset_path]

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

if __name__ == "__main__":
    subprocess.run(["make", "eval"])

    sorting_algorithm = sys.argv[1]
    if sorting_algorithm not in SORTING_ALGORITHMS:
        print("Usage: python3 auto_eval.py <sorting algorithm>")
        quit()

    os.makedirs("results/" + sorting_algorithm, exist_ok=True)
    with open("results/" + sorting_algorithm + "/" + sorting_algorithm + ".txt", mode="w") as f:
        f.write(f"Algorithm               : {sorting_algorithm}\n")
        _, output = evaluation(sorting_algorithm, "stability")
        f.write(output.strip())
        f.write("\n")
        
        for dataset_type in DATASET_TYPES:
            for dataset_size in DATASET_SIZES:
                dataset_path = "datasets/" + dataset_type + "_" + \
                    dataset_size + ".txt"
                mem, output = evaluation(sorting_algorithm, dataset_path)
                running_times = list(map(float, output.strip().split("\n")))
                f.write(f"Dataset                 : {dataset_path}\n")
                f.write(f"Peak Memory             : {mem} bytes\n")
                f.write(f"Average Running Time    : {sum(running_times) / len(running_times)} sec\n")
                f.write("Raw Data:\n")
                for running_time in running_times:
                    f.write(f"{running_time}\n")
                f.write("=" * 64 + "\n")