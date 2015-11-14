from math import factorial
from collections import Counter
from util.decorators import timer
import sys


def get_combinations(counter):
    permutations = factorial(sum(counter.itervalues()))
    duplicates = reduce(lambda x, y: x * y,
                        [factorial(v) for k, v in counter.iteritems()])

    return permutations // duplicates


def lexicographic_rank(word):
    word = list(word)

    position = 1
    for i in xrange(0, len(word) - 1):

        order = sorted(list(set(word[i:])))
        for letter in order[:order.index(word[i])]:
            counter = Counter(word[i:])
            counter[letter] -= 1
            position += get_combinations(counter)

    return position


@timer
def main():
    print lexicographic_rank('SUPERCALIFRAGILISTICEXPIALADOCIOUS')


if __name__ == '__main__':
    sys.exit(main())
