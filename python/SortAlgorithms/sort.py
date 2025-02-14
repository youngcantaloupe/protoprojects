from random import seed, sample
import time


def is_sorted(lyst):
    if not isinstance(lyst, list):
        raise TypeError("not a list")

    if not all(isinstance(x, int) for x in lyst):
        raise TypeError("contains non-integer")

    if lyst != sorted(lyst):
        return False

    return True


def is_sortable(lyst):
    if not isinstance(lyst, list):
        raise TypeError("not a list")

    if not all(isinstance(x, int) for x in lyst):
        raise TypeError("contains non-integer")

    return True


def display(tup, t):
    (sort_lyst, num_comp, num_swap) = tup

    if is_sorted(sort_lyst):
        print(f"CHECKS: {num_comp}")
        print(f"SWAPS: {num_swap}")
        print(f"TIME: {t:.5f} s")
        print()
    else:
        print("list not sorted")
        print()


def quicksort(lyst):
    try:
        is_sortable(lyst)
    except TypeError as e:
        print(e)
        return lyst, 0, 0

    def quick_help(lyst, start, end):
        if end <= start:
            return lyst, 0, 0
        high, num_comp, num_swap = quick_partition(lyst, start, end)
        l_lyst, l_comp, l_swap = quick_help(lyst, start, high)
        r_lyst, r_comp, r_swap = quick_help(lyst, high + 1, end)
        return (lyst, num_comp + l_comp + r_comp, num_swap + l_swap + r_swap)

    def quick_partition(lyst, start, end):
        num_comp, num_swap = 0, 0

        midpoint = start + (end - start) // 2
        pivot = lyst[midpoint]

        low = start
        high = end

        done = False
        while not done:
            while lyst[low] < pivot:
                low += 1
                num_comp += 1

            while pivot < lyst[high]:
                high -= 1
                num_comp += 1

            if low >= high:
                done = True
                num_comp += 1
            else:
                temp = lyst[low]
                lyst[low] = lyst[high]
                lyst[high] = temp
                low += 1
                high -= 1
                num_swap += 1

        return high, num_comp, num_swap

    return quick_help(lyst, 0, len(lyst) - 1)


def selection_sort(lyst):
    try:
        is_sortable(lyst)
    except TypeError as e:
        print(e)
        return lyst, 0, 0

    num_comp = 0
    num_swap = 0

    for i in range(len(lyst) - 1):
        i_smallest = i
        for j in range(i + 1, len(lyst)):
            num_comp += 1
            if lyst[j] < lyst[i_smallest]:
                i_smallest = j

        temp = lyst[i]
        lyst[i] = lyst[i_smallest]
        lyst[i_smallest] = temp
        num_swap += 1

    return (lyst, num_comp, num_swap)


def insertion_sort(lyst):
    try:
        is_sortable(lyst)
    except TypeError as e:
        print(e)
        return lyst, 0, 0

    num_comp = 0
    num_swap = 0

    for i in range(1, len(lyst)):
        j = i
        while j > 0:
            num_comp += 1
            if lyst[j] < lyst[j - 1]:
                num_swap += 1
                temp = lyst[j]
                lyst[j] = lyst[j - 1]
                lyst[j - 1] = temp
                j -= 1
            else:
                break

    return (lyst, num_comp, num_swap)


def mergesort(lyst):
    try:
        is_sortable(lyst)
    except TypeError as e:
        print(e)
        return lyst, 0, 0

    def merge(left, right):
        i = 0
        j = 0
        num_comp = 0
        num_swap = 0
        temp_list = []

        while i < len(left) and j < len(right):
            num_comp += 1
            if left[i] < right[j]:
                temp_list.append(left[i])
                i += 1
            else:
                temp_list.append(right[j])
                j += 1
            num_swap += 1

        while i < len(left):
            temp_list.append(left[i])
            i += 1
            num_swap += 1

        while j < len(right):
            temp_list.append(right[j])
            j += 1
            num_swap += 1

        return temp_list, num_comp, num_swap

    def merge_help(lyst, start, end):
        if end == start:
            return [lyst[start]], 0, 0

        mid = (start + end) // 2

        left, l_comp, l_swap = merge_help(lyst, start, mid)
        right, r_comp, r_swap = merge_help(lyst, mid + 1, end)

        sorted_lyst, num_comp, num_swap = merge(left, right)

        return (sorted_lyst, l_comp + r_comp + num_comp, l_swap + r_swap + num_swap)

    return merge_help(lyst, 0, len(lyst) - 1)


def main():
    xlist = [1, 2, 3, 4, "e", 6, 7, 8, 9, 10]
    xint = 1
    xsort = ([10, 9, 8, 7, 6, 5, 4, 3, 2, 1], 0, 0)

    DATA_SIZE = 10000
    seed(0)
    DATA = sample(range(DATA_SIZE * 3), k=DATA_SIZE)
    test_list = DATA.copy()
    quick_list = DATA.copy()
    merge_list = DATA.copy()
    selection_list = DATA.copy()
    insertion_list = DATA.copy()

    print(".SORT()")
    start_time = time.time()
    test_list.sort()
    end_time = time.time()
    t_time = end_time - start_time
    print(f"TIME: {t_time:.5f} s\n")

    print("QUICK SORT")
    start_time = time.time()
    qr = quicksort(quick_list)
    end_time = time.time()
    t_time = end_time - start_time
    display(qr, t_time)

    print("MERGE SORT")
    start_time = time.time()
    mr = mergesort(merge_list)
    end_time = time.time()
    t_time = end_time - start_time
    display(mr, t_time)

    print("SELECTION SORT")
    start_time = time.time()
    sr = selection_sort(selection_list)
    end_time = time.time()
    t_time = end_time - start_time
    display(sr, t_time)

    print("INSERTION SORT")
    start_time = time.time()
    ir = insertion_sort(insertion_list)
    end_time = time.time()
    t_time = end_time - start_time
    display(ir, t_time)

    print("EXCEPTIONS")
    quicksort(xlist)
    mergesort(xlist)
    selection_sort(xlist)
    insertion_sort(xlist)

    quicksort(xint)
    mergesort(xint)
    selection_sort(xint)
    insertion_sort(xint)

    display(xsort, 0)


if __name__ == "__main__":
    main()
