import sys
import pandas as pd
from scipy import stats
from delete_outliers import delete_outliers, adjust_length
from student_wilcoxon import student_test, wilcoxon_test
from plotting import three_distributions_plot, display_normality_test, create_histograms


NUMBER_OF_PARAMETER_ROWS = 0
NUMBER_OF_WARNING_ROWS = 1
NUMBER_Of_SKIP_ROWS = 5
ALPHA = 1e-3


def read_preprocess(filename):
    df = pd.read_csv(filename, skiprows=range(0, NUMBER_OF_PARAMETER_ROWS))
    return delete_outliers(df['real_time'][NUMBER_Of_SKIP_ROWS:] / 1000000000)


def main():
    # Read csv files and delete ourliers
    epoll_data = read_preprocess(sys.argv[1])
    process_data = read_preprocess(sys.argv[2])
    thread_data = read_preprocess(sys.argv[3])

    # Adjust to same length
    needed_length = max(len(epoll_data), len(process_data), len(thread_data))
    adjust_length(epoll_data, needed_length)
    adjust_length(process_data, needed_length)
    adjust_length(thread_data, needed_length)

    distributions = [
        {"name": "epoll", "data": epoll_data},
        {"name": "process", "data": process_data},
        {"name": "thread", "data": thread_data}
    ]
    # Creating bar plots of the distributions

    # single distribution plot
    create_histograms(distributions)

    # Three crawlers together on one plot
    three_distributions_plot(epoll_data, process_data, thread_data)

    
    # Testing normality
    for i in range(3):
        k2, distributions[i]["p_value"] = stats.normaltest(distributions[i]["data"])
        distributions[i]["is_normal"] = distributions[i]["p_value"] >= ALPHA

        print(distributions[i])
        display_normality_test(distributions[i])

    # if all distribution are normal, then perform a student test:
    if all([dist["is_normal"]] for dist in distributions):
        student_test(distributions)
    
    wilcoxon_test(distributions)


if __name__ == "__main__":
    main()
