from euler_lib.factor import divisors


def abundant_numbers(limit):
    """
    Find all abundant numbers less than a given limit
    :param limit: Cutoff for list
    :return: (list) Abundant numbers from 1 to limit
    """

    return [x for x in xrange(1, limit) if sum(divisors(x)) > 2 * x]


def sieve_eratosthenes(limit):
    """
    Find all primes less than or equal to limit
    :param limit: ceiling for prime sieve
    :return: generator of primes lte limit
    """

    sieve = [False] * 2 + [True] * (limit - 1)  # Initialize 0, 1 to false and others to true

    for i, state in enumerate(sieve):
        if state is True:
            yield i
            for j in xrange(i * i, limit + 1, i):
                sieve[j] = False


def triangle_number_gen(ceil=None):
    total, cur = 1, 2
    while True:
        yield total
        total, cur = total + cur, cur + 1
        if ceil and total > ceil:
            break


def pentagonal_number_gen():
    total, cur = 1, 4
    while True:
        yield total
        total, cur = total + cur, cur + 3


def collatz_gen(num):
    """
    Generator for the Collatz sequence
    :param num:
    :return: The next element in the Collatz sequence for num
    """

    while True:
        if num % 2 == 0:
            num /= 2
        else:
            num = 3 * num + 1
        yield num


def collatz_chain(num):
    """
    :param num:
    :return: a list of the Collatz sequence from num until 1
    """

    collatz_list = [num]
    for i in collatz_gen(num):
        collatz_list.append(i)
        if i == 1:
            break

    return collatz_list


def xfibonacci():
    """
    Fibonacci generator
    :return: (int) next Fibonacci number
    """
    m, n = 1, 1
    while True:
        yield m
        m, n = n, m + n


def rotations(num):
    """
    Returns a list of all rotations of a number
    :param num:
    :return: (list) rotations of num
    """
    return [int(str(num)[x:] + str(num)[:x]) for x in xrange(0, len(str(num)))]
