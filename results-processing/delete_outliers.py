import numpy as np
from scipy.stats import iqr
import numpy


def delete_outliers(data):
    """
    Deletes outliers based on Inter Quartile Range.

    :param data: an array-like object with numeric data
    :return: array without outliers
    """
    iqr(data, axis=0)
    Q1 = np.quantile(data, 0.25)
    Q3 = np.quantile(data, 0.75)
    IQR = Q3 - Q1
    return list(filter(lambda x: Q1 - 1.5 * IQR <= x <= Q3 + 1.5 * IQR, data))


def adjust_length(data, needed_length):
    mean_value = numpy.mean(data)
    data += [mean_value] * (needed_length - len(data))


# Testing
if __name__ == "__main__":
    test_data = [1, 2, 3, 4, -60, 90, 56, 3, 2, 3, 2, 5, 4, 6, -100]
    test_data = delete_outliers(test_data)
    print(len(test_data))
    adjust_length(test_data, len(test_data) + 10)
    print(len(test_data))
    print(test_data)
