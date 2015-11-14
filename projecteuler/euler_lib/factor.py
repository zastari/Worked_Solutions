from math import sqrt


def divisors(num, proper=False):
    """
    Calculate all divisors of num
    :param num:
    :param proper: (bool) Only include proper divisors (not num itself) if True
    :return: (list) all divisors of num
    """

    d = list(set(reduce(
        lambda x, y: x + y,
        [[x, num/x] for x in xrange(1, int(sqrt(num))+1) if num % x == 0]
    )))
    if proper:
        d.remove(num)
    return d


def factor_naive(num):
    """
    Factorize a number using naive method. Checks all values from 2 to sqrt(num).
    :param num: Number to factorize
    :return: List of factors of num
    """

    i = 2
    factors = []

    while i < sqrt(num):
        while num % i == 0:
            factors.append(i)
            num /= i

        i += 1
    factors.append(num)

    return factors


def factor_np(num):
    """
    Factorize a number and return the factors and powers as two lists
    :param num: Number to factorize
    :return: (list, list) factors and powers of num
    """

    factor_list = factor_naive(num)
    return set((num, factor_list.count(num)) for num in set(factor_list))


def count_divisors(num):
    """
    Find the amount of numbers that divide num including 1 and num itself
    :param num: Number to find divisors for
    :return: List of divisors of num
    """

    prime_factors = factor_naive(num)
    multiplicities = []

    # For a factorization p^k * q^l * r^m we have (k+1) * (q+1) * (r+1) combinations of factors
    for i in set(prime_factors):
        multiplicities.append(prime_factors.count(i) + 1)

    return reduce(lambda x, y: x * y, multiplicities)
