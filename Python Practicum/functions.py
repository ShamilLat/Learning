from typing import List
from typing import Tuple


def prod_non_zero_diag(X: List[List[int]]) -> int:
    check = False
    prod = 1
    i = 0
    for i in range(min(len(X), len(X[i]))):
        if X[i][i] != 0:
            check = True
            prod *= X[i][i]
    if check:
        return prod
    else:
        return -1


def are_multisets_equal(x: List[int], y: List[int]) -> bool:
    for i in x:
        if (i not in y) or y.count(i) != x.count(i):
            return False
    return True


def max_after_zero(x: List[int]) -> int:
    l = [x[i] for i in range(1, len(x)) if x[i - 1] == 0]
    if len(l) == 0:
        return -1
    else:
        return max(l)


def convert_image(image: List[List[List[float]]], weights: List[float]) -> List[List[float]]:
    l1 = []
    for x in image:
        l2 = []
        for y in x:
            sum = 0
            for z in range(len(y)):
                sum += y[z] * weights[z]
            l2.append(sum)
        l1.append(l2)
    return l1


def run_length_encoding(x: List[int]) -> Tuple[List[int], List[int]]:
    l = []
    y = []
    i = 0
    while i < len(x):
        y.append(x[i])
        count = 0
        pos = i
        while i < len(x) and x[i] == x[pos]:
            count += 1
            i += 1
        l.append(count)
    return (y, l)


def pairwise_distance(X: List[List[float]], Y: List[List[float]]) -> List[List[float]]:
    l1 = []
    for x in X:
        l2 = []
        for y in Y:
             p = 0
             for i in range(len(y)):
                 p += (x[i] - y[i]) ** 2
             l2.append(p ** 0.5)
        l1.append(l2)
    return l1