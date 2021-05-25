import sys
import pandas as pd
import matplotlib.pyplot as plt
from scipy import stats
import plotly.express as px
from plotly.subplots import make_subplots
import plotly.graph_objects as go
import seaborn as sns

NUMBER_OF_PARAMETER_ROWS = 9
NUMBER_OF_WARNING_ROWS = 1
NUMBER_Of_SKIP_ROWS = 5

if __name__ == "__main__":
    ###################################################################################################################
    # Read csv files
    epoll_csv = sys.argv[1]
    process_csv = sys.argv[2]
    thread_csv = sys.argv[3]

    epoll_data = pd.read_csv(epoll_csv,
                             skiprows=range(0, NUMBER_OF_PARAMETER_ROWS))
    process_data = pd.read_csv(process_csv,
                               skiprows=range(0, NUMBER_OF_PARAMETER_ROWS))
    thread_data = pd.read_csv(thread_csv,
                              skiprows=range(0, NUMBER_OF_PARAMETER_ROWS))

    ###################################################################################################################
    # Plot customizations
    custom_labels = {"x": "Time, ns",
                     "y": "Number of iterations"}

    ###################################################################################################################
    # Creating bar plots of the distributions
    # Create outlay for three plots
    # TODO:
    # bar_figs = make_subplots(rows=1, cols=3)

    # Epoll plot
    # TODO: replace by a function
    # epoll_fig_test = go.Bar(x=epoll_data['real_time'][NUMBER_Of_SKIP_ROWS:],
    #                         y=[i for i in range(0, len(epoll_data['real_time'][NUMBER_Of_SKIP_ROWS:]))])

    epoll_fig = px.histogram(x=epoll_data['real_time'][NUMBER_Of_SKIP_ROWS:],
                             nbins=50,
                             title="Epoll results distribution",
                             labels=custom_labels)
    epoll_fig.write_image("result-plots/epoll-distribution.png")

    # Process per socket plot
    process_fig = px.histogram(x=process_data['real_time'][NUMBER_Of_SKIP_ROWS:],
                               nbins=50,
                               title="Process per socket results distribution",
                               labels=custom_labels)
    process_fig.write_image("result-plots/process-distribution.png")

    # Thread per socket plot
    thread_fig = px.histogram(x=thread_data['real_time'][NUMBER_Of_SKIP_ROWS:],
                              nbins=50,
                              title="Thread per socket results distribution",
                              labels=custom_labels)
    thread_fig.write_image("result-plots/thread-distribution.png")

    # Add subplots to the main plot
    # TODO:
    # bar_figs.add_trace(
    #     epoll_fig_test,
    #     row=1, col=1
    # )
    # bar_figs.write_image("result-plots/distributions.png")
    ###################################################################################################################
    #
    # thread_fig = px.bar(x=thread_data, y=range(0, len(thread_data)), title="Thread per socket results distribution",
    #                     labels=custom_labels)
    # thread_fig.update_xaxes(type='linear')
    # thread_fig.write_image("result-plots/thread-distribution.png")
    #
    # # Creating density plots and histograms
    # ax1 = plt.subplot(1, 3, 1)
    # ax1.hist(epoll_data, bins=40,
    #          color='darkblue', edgecolor='black')
    #
    # sns.distplot(epoll_data, hist=True, kde=True,
    #              bins=36, color='darkblue',
    #              hist_kws={'edgecolor': 'black'},
    #              kde_kws={'linewidth': 4})
    # plt.savefig("result-plots/epoll-density.png")
    #
    # sns.distplot(process_data, hist=True, kde=True,
    #              bins=36, color='red',
    #              hist_kws={'edgecolor': 'black'},
    #              kde_kws={'linewidth': 4})
    # plt.savefig("result-plots/process-density.png")
    #
    # sns.distplot(thread_data, hist=True, kde=True,
    #              bins=36, color='darkblue',
    #              hist_kws={'edgecolor': 'black'},
    #              kde_kws={'linewidth': 4})
    # plt.savefig("result-plots/thread-density.png")
    #
    # # Testing normality
    # alpha = 1e-3
    # epoll_k2, epoll_p = stats.normaltest(epoll_data)
    # process_k2, process_p = stats.normaltest(process_data)
    # thread_k2, thread_p = stats.normaltest(thread_data)
    #
    # normal_epoll = epoll_p >= alpha
    # normal_process = process_p >= alpha
    # normal_thread = thread_p >= alpha
    #
    # # Displaying normality results
    # print("NORMALITY TESTING\n" + "*" * 50)
    # print("Epoll:")
    # if normal_epoll:
    #     print(f"Normal distribution, with p = {epoll_p}\n" + "*" * 50)
    # else:
    #     print(f"Not a normal distribution, with p = {epoll_p}\n" + "*" * 50)
    #
    # print("Process per socket:")
    # if normal_epoll:
    #     print(f"Normal distribution, with p = {process_p}\n" + "*" * 50)
    # else:
    #     print(f"Not a normal distribution, with p = {process_p}\n" + "*" * 50)
    #
    # print("Thread per socket:")
    # if normal_epoll:
    #     print(f"Normal distribution, with p = {thread_p}\n" + "*" * 50)
    # else:
    #     print(f"Not a normal distribution, with p = {thread_p}\n")
    #
    # if normal_epoll and normal_process and normal_thread:
    #     # Hypotheses that all the data has normal distribution cannot be rejected
    #     # Performing Student t-test:
    #     t_stat, p = stats.ttest_ind(epoll_data, process_data)
    # else:
    #     # Hypotheses that all the data has normal distribution can be rejected (or at least some of the data)
    #     # Performing Wilcoxon test:
    #     stat, p = stats.wilcoxon(epoll_data, process_data)
