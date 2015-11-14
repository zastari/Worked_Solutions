from math import sqrt
import sys

phi = (1 + sqrt(5))/2


def fib_exact(n):
    return int(((phi ** n) - (-1 / phi) ** n) / sqrt(5))


def main():
    print fib_exact(1)
    print fib_exact(2)
    print fib_exact(100)


if __name__ == '__main__':
    sys.exit(main())
