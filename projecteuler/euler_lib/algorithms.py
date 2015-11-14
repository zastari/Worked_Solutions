import operator


def next_permutation(n):
    n = str(n)
    try:
        a = next(x for x in xrange(len(n) - 2, -1, -1) if n[x] < n[x + 1])
    except StopIteration:
        return None
    else:
        b = next(x for x in xrange(len(n) - 1, a, -1) if n[x] > n[a])
        n = list(n)
        n[a], n[b] = n[b], n[a]
        return int(''.join(n[:a + 1] + n[:a:-1]))


def choose(n, r):
    if r > n or r < 0:
        return 0

    if r == n:
        return 1

    r = max(r, n - r)

    numerator = reduce(operator.mul, xrange(n, r, -1))
    denominator = reduce(operator.mul, xrange(1, n - r + 1))

    return numerator // denominator


def partition_integer(number, partitions, index_limit=None):
    """
    Returns the number of ways a number can be partitioned by the given partitions
    :param number: (int) number to partition
    :param partitions: (list) list of integers to partition number by
    :param index_limit: maximal index to use in partitions for recursion (should be None on call)
    :return: (int) Number of ways in which number can be partitioned by partitions
    """
    if index_limit is None:
        index_limit = len(partitions) - 1

    if index_limit < 0 or number < 0:
        return 0
    elif number == 0:
        return 1

    return partition_integer(number, partitions, index_limit=(index_limit - 1)) + \
           partition_integer(number - partitions[index_limit], partitions,
                             index_limit=index_limit)


def triangle_sum(triangle):
    """
    Calculates the maximum sum path through a triangle of arbitrary depth
    A triangle is defined to be a list of lists of the form [[a_1],[b_1,b_2],...[x_1,...,x_n]]
    :param triangle: nested triangle list
    :return: maximal sum through triangle, list of elements through triangle that create this sum
    """

    branches = [[triangle[0][0]]]
    for depth in xrange(1, len(triangle)):
        branches.append(
            branches[depth - 1] + [triangle[depth][depth]])  # Extend rightmost branch

        # Find winning path to each interior index
        # Move right-to-left to prevent iterative updates from affecting comparisons
        for col in xrange(depth - 1, 0, -1):
            if sum(branches[col - 1]) > sum(branches[col]):
                branches[col] = branches[col - 1] + [triangle[depth][col]]
            else:
                branches[col].append(triangle[depth][col])

        branches[0].append(triangle[depth][0])  # Extend leftmost branch

    return max(sum(branch) for branch in branches)
