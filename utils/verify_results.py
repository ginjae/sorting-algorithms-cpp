import os
import glob

def verify_result(file_path):
    with open(file_path, mode='r') as f:
        prev = None
        line_num = 0

        for line in f:
            line_num += 1
            line = line.strip()

            try:
                current = int(line)
            except ValueError:
                print(f"!!!!! {file_path}, line: {line_num} is not a integer !!!!!")
                return False

            if prev is not None and current < prev:
                print(f"!!!!! {file_path},line: {line_num} -> incorrectly sorted !!!!!")
                return False

            prev = current
    print(file_path + " is correctly sorted")
    return True

if __name__ == "__main__":
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    results = os.path.join(root, "results")
    for name in os.listdir(results):
        if os.path.isdir(os.path.join(results, name)):
            result_files = glob.glob(os.path.join(results, name, "*.txt"))
            for file in result_files:
                if not verify_result(os.path.relpath(file)):
                    quit()
    print("=" * 64)
    print("all files are correctly sorted")