import numpy as np
from math import sqrt
from functools32 import lru_cache
from euler_lib import factor


def amicable_pair(num):
    """
    Determines if num is amicable and returns its copair element if it is
    :param num:
    :return: 0 if num is not amicable, num's copair element if it is
    """
    copair = sum(factor.divisors(num)) - num
    return copair if (sum(
        factor.divisors(copair)) - copair) == num and copair != num else 0


def is_palindrome(num):
    """
    Determines whether a number is a palindrome.
    :param num: Input number to check if palindromic
    :return: boolean
    """
    return str(num) == str(num)[::-1]


def is_pandigital(num, lower=1, upper=9):
    """
    Returns True if num is pandigital else False
    :param num: (int)
    :kwarg lower: (int) lower limit for pandigital check
    :kwarg limit: (int) upper limit for pandigital check
    :return: (bool)
    """
    pan_digits = {str(x) for x in xrange(lower, upper + 1)}
    num_digits = [str(x) for x in str(num)]
    return pan_digits.issubset(num_digits) and len(num_digits) == (
        upper - lower + 1)


@lru_cache(maxsize=1024)
def is_prime(num):
    """
    Returns True if num is prime else False
    :param num:
    :return: (bool) Primality of num
    """
    if num == 1:
        return False

    for i in xrange(2, int(sqrt(num)) + 1):
        if num % i == 0:
            return False

    return True


def is_triangular(num):
    return ((sqrt(8 * num + 1) - 1) / 2).is_integer()


def is_pentagonal(num):
    return ((sqrt(24 * num + 1) + 1) / 6).is_integer()


def is_hexagonal(num):
    return ((sqrt(8 * num + 1) + 1) / 4).is_integer()


def max_2array_seq_prod(matrix, seq_len):
    """
    Returns the maximal product of seq_len sequential elements of a matrix.
    Left -> Right, Up -> Down, and Diagonals are searched

    :param matrix: numpy matrix to search
    :param seq_len: number of sequential elements to multiply
    :return: (maximum product, list of elements that generated the product)
    """
    dim = matrix.shape[0]
    max_product = 0
    max_slice = []

    for i in range(0, dim):
        for j in range(0, dim):
            # Right
            if j <= dim - seq_len:
                cur_slice = matrix[i, j:j + seq_len]
                cur_product = cur_slice.prod()
                if cur_product > max_product:
                    max_slice, max_product = cur_slice, cur_product
            # Down
            if i <= dim - seq_len:
                cur_slice = matrix[i:i + seq_len, j]
                cur_product = cur_slice.prod()
                if cur_product > max_product:
                    max_slice, max_product = cur_slice, cur_product
            # Down-Right
            if i <= dim - seq_len and j <= dim - seq_len:
                cur_slice = np.array(
                    [matrix[i + x, j + x] for x in xrange(0, seq_len)])
                cur_product = cur_slice.prod()
                if cur_product > max_product:
                    max_slice, max_product = cur_slice, cur_product
            # Up-Right
            if i >= seq_len and j <= dim - seq_len:
                cur_slice = np.array(
                    [matrix[i - x, j + x] for x in xrange(0, seq_len)])
                cur_product = cur_slice.prod()
                if cur_product > max_product:
                    max_slice, max_product = cur_slice, cur_product

    return max_product, max_slice
