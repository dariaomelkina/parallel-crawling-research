import sys
import pandas
from scipy import stats
import plotly.express as px

if __name__ == "__main__":
    # epoll_csv = sys.argv[1]
    # process_csv = sys.argv[2]
    # thread_csv = sys.argv[3]
    # TODO: read csv file

    # TODO: change to real input data
    epoll_data = [134, 456, 213, 234, 278, 190, 191, 135, 476, 223, 214, 178, 199, 171, 234, 356, 313, 334, 378, 290, 291]
    process_data = [134, 456, 213, 234, 278, 190, 191, 135, 476, 223, 214, 178, 199, 171, 234, 356, 313, 334, 378, 290, 291]
    thread_data = [134, 456, 213, 234, 278, 190, 191, 135, 476, 223, 214, 178, 199, 171, 234, 356, 313, 334, 378, 290, 291]

    # I dont think we need a scatter plot
    # fig = px.scatter(x=data, y=range(0, len(data)))

    # Creating bar plots of the distributions
    fig = px.bar(x=epoll_data, y=range(0, len(epoll_data)))

    # Testing normality
    alpha = 1e-3
    epoll_k2, epoll_p = stats.normaltest(epoll_data)
    process_k2, process_p = stats.normaltest(process_data)
    thread_k2, thread_p = stats.normaltest(thread_data)

    normal_epoll = epoll_p >= alpha
    normal_process = process_p >= alpha
    normal_thread = thread_p >= alpha

    if normal_epoll and normal_process and normal_thread:
        print("normal")
        # Hypotheses that data has normal distribution cannot be rejected
        # Performing Student t-test
        t_stat, p = stats.ttest_ind(epoll_data, process_data)
    else:
        # Hypotheses that data has normal distribution can be rejected
        # Performing Wilcoxon test
        stat, p = stats.wilcoxon(epoll_data, process_data)
