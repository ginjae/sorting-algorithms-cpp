import os
import glob

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

def get_answer(dataset_path):
    with open(dataset_path, mode="r") as f:
        answer = [int(line.strip()) for line in f if line.strip()]
        answer.sort()
        return answer

def verify_result(result_path):
    answer = answers[os.path.basename(result_path)]
    with open(result_path, mode='r') as f:
        result = [int(line.strip()) for line in f if line.strip()]
        for i in range(len(answer)):
            if answer[i] != result[i]:
                print("!!! " + result_path + ": line ", i + 1)
                return False
        
    print(result_path + " is correctly sorted")
    return True

if __name__ == "__main__":
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    answers = dict()
    for dataset_type in DATASET_TYPES:
        for dataset_size in DATASET_SIZES:
            dataset_name = dataset_type + "_" + dataset_size + ".txt"
            dataset_path = os.path.join(root, "datasets", dataset_name)
            answers[dataset_name] = get_answer(dataset_path)

    results = os.path.join(root, "results")
    
    total = 0
    incorrect = 0
    for name in os.listdir(results):
        if os.path.isdir(os.path.join(results, name)):
            result_files = glob.glob(os.path.join(results, name, "*.txt"))
            for file in result_files:
                total += 1
                if not verify_result(os.path.relpath(file)):
                    incorrect += 1
    print("=" * 64)
    print(f"total: {total}")
    print(f"incorrect: {incorrect}")