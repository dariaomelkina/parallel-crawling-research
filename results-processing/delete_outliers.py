import numpy as np
from scipy.stats import iqr


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


# Testing
if __name__ == "__main__":
    test_data = [1, 2, 3, 4, -60, 90, 56, 3, 2, 3, 2, 5, 4, 6, -100]
    print(delete_outliers(test_data))
