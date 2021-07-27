import numpy as np
from scipy import stats

ALPHA = 1e-3



def display_normality_test(distribution):
    name = distribution["name"]
    data = distribution["data"]
    k2, p_value = stats.normaltest(data)

    distribution["is_normal"] = p_value >= ALPHA

    print("*" * 50)
    print(f"NORMALITY TESTING {name}\n" + "*" * 50)
    print(f"Mean = {round(np.mean(data), 2)}")
    print(f"Standard deviation = {round(np.std(data), 2)}")

    if distribution["is_normal"]:
        print(f"Normal distribution, with p = {'%.2g' % p_value}\n" + "*" * 50 + "\n\n")
    else:
        print(f"Not a normal distribution, with p = {'%.2g' % p_value}\n" + "*" * 50 + "\n\n")


def compare_distributions(distribution1, distribution2):
    if distribution1["is_normal"] and distribution2["is_normal"]:
        test_name = "STUDENT T-TEST"
        test = stats.ttest_ind
        to_compare = np.mean
        to_compare_name = "mean"
    else:
        test_name = "WILCOXON TEST"
        test = stats.ranksums
        to_compare = np.min
        to_compare_name = "minimum"

    name1 = distribution1['name']
    name2 = distribution2['name']

    data1, data2 =distribution1['data'], distribution2['data']
    
    print("\n")
    print("*" * 95)
    print(f"COMPARING {name1} AND {name2}")
    print(f"{test_name}\n" + "*" * 95)
    stat, p = test(data1, data2)
    print(f"Test statistic = {round(stat, 2)}\np = {'%.2g' % p}")


    if p >= ALPHA:
        print(f"We cannot reject hypotheses, that {name1} and {name2} "
              "are not significantly different \nfrom each other.\n" + "*" * 95)
    else:
        print(f"We reject hypotheses, that {name1} and {name2} "
              "are not significantly different \nfrom each other. (they are different, in other words)")
        print(f"Comparing {to_compare_name}s:")
        m1 = round(to_compare(data1), 2)
        m2 = round(to_compare(data2), 2)

        print(f"{name1} {to_compare_name} = {m1}")
        print(f"{name2} {to_compare_name} = {m2}")
        if m1 < m2:
            print(f"{name1} has {to_compare_name} smaller by {round(100 - (m1 / m2) * 100, 2)}%\n" + "*" * 95)
        else:
            print(f"{name2} has {to_compare_name} smaller by {round(100 - (m2 / m1) * 100, 2)}%\n" + "*" * 95)
