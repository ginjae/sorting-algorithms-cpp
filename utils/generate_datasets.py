import os
import csv
import random

SEED = 20211061

def generate_random_dataset(size):
    data = list(range(size))
    random.shuffle(data)
    return data

def generate_dense_random_dataset(size):
    return [random.randint(0, 9) for _ in range(size)]

def generate_ascending_dataset(size):
    return list(range(size))

def generate_descending_dataset(size):
    return list(reversed(range(size)))

def generate_partially_sorted_dataset(size, shuffle_ratio=0.5):
    data = list(range(size))
    start_i = random.randint(0, int(size * shuffle_ratio))
    end_i = start_i + int(size * shuffle_ratio)
    random.shuffle(data)
    for i in range(start_i, end_i):
        data[i] = i
    return data

def write_csv(data, file_path):
    with open(file_path, mode="w", newline="") as f:
        writer = csv.writer(f)
        for d in data:
            writer.writerow([d])

def generate_all_datasets(dir_path="datasets", sizes=(1_000, 10_000, 100_000, 1_000_000)):
    random.seed(SEED)
    os.makedirs(dir_path, exist_ok=True)

    for size in sizes:
        random_data = generate_random_dataset(size)
        write_csv(random_data, os.path.join(dir_path, f"random_{size}.txt"))

        dense_random_data = generate_dense_random_dataset(size)
        write_csv(dense_random_data, os.path.join(dir_path, f"dense_random_{size}.txt"))

        ascending_data = generate_ascending_dataset(size)
        write_csv(ascending_data, os.path.join(dir_path, f"ascending_{size}.txt"))

        descending_data = generate_descending_dataset(size)
        write_csv(descending_data, os.path.join(dir_path, f"descending_{size}.txt"))
        
        partially_sorted_data = generate_partially_sorted_dataset(size)
        write_csv(partially_sorted_data, os.path.join(dir_path, f"partially_sorted_{size}.txt"))

if __name__ == "__main__":
    generate_all_datasets()