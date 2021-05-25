import sys
import pandas
import matplotlib.pyplot as plt
from scipy import stats
import plotly.express as px
import seaborn as sns

if __name__ == "__main__":
    # epoll_csv = sys.argv[1]
    # process_csv = sys.argv[2]
    # thread_csv = sys.argv[3]
    # TODO: read csv file

    # TODO: change to real input data
    epoll_data = [134, 456, 213, 234, 278, 190, 191, 135, 476, 223, 214, 178, 199, 171, 234, 356, 313, 334, 378, 290,
                  291]
    process_data = [134, 456, 213, 234, 278, 190, 191, 135, 476, 223, 214, 178, 199, 171, 234, 356, 313, 334, 378, 290,
                    291]
    thread_data = [134, 456, 213, 234, 278, 190, 191, 135, 476, 223, 214, 178, 199, 171, 234, 356, 313, 334, 378, 290,
                   291]

    # Plot customizations
    # TODO: which metrics do we have?
    custom_labels = {"x": "time, ns",
                     "y": "number of iterations"}

    # Creating bar plots of the distributions
    # TODO: replace by a function
    epoll_fig = px.bar(x=epoll_data, y=range(0, len(epoll_data)), title="Epoll results distribution",
                       labels=custom_labels)
    epoll_fig.update_xaxes(type='linear')
    epoll_fig.write_image("result-plots/epoll-distribution.png")

    process_fig = px.bar(x=process_data, y=range(0, len(process_data)), title="Process per socket results distribution",
                         labels=custom_labels)
    process_fig.update_xaxes(type='linear')
    process_fig.write_image("result-plots/process-distribution.png")

    thread_fig = px.bar(x=thread_data, y=range(0, len(thread_data)), title="Thread per socket results distribution",
                        labels=custom_labels)
    thread_fig.update_xaxes(type='linear')
    thread_fig.write_image("result-plots/thread-distribution.png")

    # Creating density plots and histograms
    # TODO: finish
    sns.distplot(epoll_data, hist=True, kde=True,
                 bins=int(180 / 5), color='darkblue',
                 hist_kws={'edgecolor': 'black'},
                 kde_kws={'linewidth': 4})

    plt.savefig("result-plots/seaborn-experiment.png")

    # Testing normality
    alpha = 1e-3
    epoll_k2, epoll_p = stats.normaltest(epoll_data)
    process_k2, process_p = stats.normaltest(process_data)
    thread_k2, thread_p = stats.normaltest(thread_data)

    normal_epoll = epoll_p >= alpha
    normal_process = process_p >= alpha
    normal_thread = thread_p >= alpha

    # Displaying normality results
    print("NORMALITY TESTING\n" + "*" * 50)
    print("Epoll:")
    if normal_epoll:
        print(f"Normal distribution, with p = {epoll_p}\n" + "*" * 50)
    else:
        print(f"Not a normal distribution, with p = {epoll_p}\n" + "*" * 50)

    print("Process per socket:")
    if normal_epoll:
        print(f"Normal distribution, with p = {process_p}\n" + "*" * 50)
    else:
        print(f"Not a normal distribution, with p = {process_p}\n" + "*" * 50)

    print("Thread per socket:")
    if normal_epoll:
        print(f"Normal distribution, with p = {thread_p}\n" + "*" * 50)
    else:
        print(f"Not a normal distribution, with p = {thread_p}\n")

    if normal_epoll and normal_process and normal_thread:
        # Hypotheses that all the data has normal distribution cannot be rejected
        # Performing Student t-test:
        t_stat, p = stats.ttest_ind(epoll_data, process_data)
    else:
        # Hypotheses that all the data has normal distribution can be rejected (or at least some of the data)
        # Performing Wilcoxon test:
        stat, p = stats.wilcoxon(epoll_data, process_data)
