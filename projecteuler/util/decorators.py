import timeit


def timer(func):
    def wrapper(*args, **kwargs):
        start_time = timeit.default_timer()
        func(*args, **kwargs)
        end_time = timeit.default_timer()
        print "Execution time: {:.6f} seconds".format(end_time - start_time)

    return wrapper
