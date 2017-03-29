#! /usr/bin/env python

def sorted_order(a, b):
    return a > b


def reverse_order(a, b):
    return a < b


def strange_order(a, b):
    if a == 0 or b == 0:
        return 0
    else:
        return a % 2


def insertion_sort(numbers, compare_cb):
    
    for i in range(1, len(numbers)):
        j = i
        while j > 0:
            if compare_cb(numbers[j-1], numbers[j]):
                numbers[j-1], numbers[j] = numbers[j], numbers[j-1]
                j -= 1
            else:
                break

    return numbers


def bubble_sort(numbers, compare_cb):

    for i, _ in enumerate(numbers):
        for j, _ in enumerate(numbers[:-1]):
            if compare_cb(numbers[j], numbers[j+1]):
                numbers[j], numbers[j+1] = numbers[j+1], numbers[j]

    return numbers 


def test_sorting(numbers, sort_cb, compare_cb):

    sort = (str(i) for i in sort_cb(numbers, compare_cb))
    print(', '.join(sort))


if __name__ == "__main__":

    from sys import argv

    numbers = [int(i) for i in argv[1:]]

    test_sorting(numbers, insertion_sort, sorted_order)
    test_sorting(numbers, insertion_sort, reverse_order)
    test_sorting(numbers, insertion_sort, strange_order)
    test_sorting(numbers, bubble_sort, sorted_order)
    test_sorting(numbers, bubble_sort, reverse_order)
    test_sorting(numbers, bubble_sort, strange_order)

