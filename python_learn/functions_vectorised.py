import numpy as np
from typing import Tuple

def prod_non_zero_diag(X: np.ndarray) -> int:
    diag = np.diag(X)
    x = np.array(diag[diag != 0])
    if len(x) == 0:
        return -1
    else:
        mul = 1;
        for i in x:
            mul *= i
        return mul


def are_multisets_equal(x: np.ndarray, y: np.ndarray) -> bool:
    return np.array_equal(np.sort(x), np.sort(y))


def max_after_zero(x: np.ndarray) -> int:
    zero_poses = np.argwhere(x == 0) + 1
    if len(zero_poses) == 0:
        return -1
    if zero_poses[-1] == len(x):
        zero_poses = zero_poses[:-1]
    if len(zero_poses) == 0:
        return -1
    return x[zero_poses].max()


def convert_image(image: np.ndarray, weights: np.ndarray) -> np.ndarray:
    return np.sum(image * weights, axis=2)


def run_length_encoding(x: np.ndarray) -> Tuple[np.ndarray, np.ndarray]:
    x = np.asarray(x)
    
    starts = np.r_[0, np.flatnonzero(~np.isclose(x[1:], x[:-1], equal_nan=True)) + 1]
    counts = np.diff(np.r_[starts, len(x)])
    values = x[starts]
    return (values, counts)


def pairwise_distance(X: np.ndarray, Y: np.ndarray) -> np.ndarray:
    x = np.square(X[:, None, :] - Y[None, :, :])
    return np.sqrt(np.sum(x, axis = -1))