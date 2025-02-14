from random import seed, sample
import math


def make_data(data_size):
    seed(0)
    data = sample(range(data_size * 3), k=data_size)
    data.sort()
    while True:
        yield data


def linear_search(lyst, target):
    count = 0
    for index in lyst:
        count += 1
        if index == target:
            return True, count
    return False, count


def binary_search(lyst, target):
    count = 0
    lo = 0
    hi = len(lyst) - 1
    mid = 0
    found = False

    while not found and lo <= hi:
        count += 1
        mid = (lo + hi) // 2
        if lyst[mid] == target:
            found = True
            return found, count
        elif lyst[mid] > target:
            hi = mid - 1
        else:
            lo = mid + 1

    return found, count


def jump_search(lyst, target):
    n = len(lyst)
    step = int(math.sqrt(n))
    i = 0
    j = step
    count = 0

    while True:
        count += 1
        if target > lyst[j - 1]:
            i = j
            j = i + step
            if j >= n:
                j = n
                break
        else:
            break

    for index in range(i, j):
        count += 1
        if lyst[index] == target:
            return True, count

    return False, count


def main():
    pass


if __name__ == "__main__":
    main()
