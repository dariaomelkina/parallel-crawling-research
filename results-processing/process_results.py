import sys
import pandas as pd
from scipy import stats
import numpy
import plotly.express as px
import plotly.graph_objects as go

NUMBER_OF_PARAMETER_ROWS = 11
NUMBER_OF_WARNING_ROWS = 1
NUMBER_Of_SKIP_ROWS = 5

if __name__ == "__main__":
    ###################################################################################################################
    # Read csv files
    epoll_df = pd.read_csv(sys.argv[1],
                           skiprows=range(0, NUMBER_OF_PARAMETER_ROWS))
    process_df = pd.read_csv(sys.argv[2],
                             skiprows=range(0, NUMBER_OF_PARAMETER_ROWS))
    thread_df = pd.read_csv(sys.argv[3],
                            skiprows=range(0, NUMBER_OF_PARAMETER_ROWS))

    epoll_data = epoll_df['real_time'][NUMBER_Of_SKIP_ROWS:] / 1000000000
    process_data = process_df['real_time'][NUMBER_Of_SKIP_ROWS:] / 1000000000
    thread_data = thread_df['real_time'][NUMBER_Of_SKIP_ROWS:] / 1000000000

    ###################################################################################################################
    # Plot customizations
    custom_labels = {"x": "Time, s",
                     "y": "Number of iterations"}

    ###################################################################################################################
    # Creating bar plots of the distributions

    # Epoll plot
    epoll_fig = px.histogram(x=epoll_data,
                             nbins=50,
                             title="Epoll results distribution",
                             labels=custom_labels)
    epoll_fig.write_image("result-plots/epoll-distribution.png")

    # Process per socket plot
    process_fig = px.histogram(x=process_data,
                               nbins=50,
                               title="Process per socket results distribution",
                               labels=custom_labels)
    process_fig.write_image("result-plots/process-distribution.png")

    # Thread per socket plot
    thread_fig = px.histogram(x=thread_data,
                              nbins=50,
                              title="Thread per socket results distribution",
                              labels=custom_labels)
    thread_fig.write_image("result-plots/thread-distribution.png")

    # Three crawlers together on one plot
    fig = go.Figure()
    fig.add_trace(go.Histogram(
        x=epoll_data,
        name='epoll',
        xbins=dict(
            start=0,
            end=30,
            size=0.01,
        ),
        autobinx=False,
        marker_color='steelblue',
        opacity=0.75
    ))
    fig.add_trace(go.Histogram(
        x=process_data,
        name='process per socket',
        xbins=dict(
            start=0,
            end=30,
            size=0.01,
        ),
        autobinx=False,
        marker_color='blueviolet',
        opacity=0.75
    ))
    fig.add_trace(go.Histogram(
        x=thread_data,
        name='thread per socket',
        xbins=dict(
            start=0,
            end=30,
            size=0.01,
        ),
        autobinx=False,
        marker_color='deeppink',
        opacity=0.75
    ))

    fig.update_layout(
        title_text='Benchmarking Results',
        xaxis_title_text='Time, s',
        yaxis_title_text='Count',
        bargap=0.2,
        bargroupgap=0.1
    )
    fig.write_image("result-plots/distributions.png")

    ###################################################################################################################
    # Testing normality
    alpha = 1e-3
    epoll_k2, epoll_p = stats.normaltest(epoll_data)
    process_k2, process_p = stats.normaltest(process_data)
    thread_k2, thread_p = stats.normaltest(thread_data)

    normal_epoll = epoll_p >= alpha
    normal_process = process_p >= alpha
    normal_thread = thread_p >= alpha

    ###################################################################################################################
    # Displaying normality results
    print("NORMALITY TESTING\n" + "*" * 50)
    print("Epoll:")
    print(f"Mean = {numpy.mean(epoll_data)}")
    if normal_epoll:
        print(f"Normal distribution, with p = {epoll_p}\n" + "*" * 50)
    else:
        print(f"Not a normal distribution, with p = {epoll_p}\n" + "*" * 50)

    print("Process per socket:")
    print(f"Mean = {numpy.mean(process_data)}")
    if normal_process:
        print(f"Normal distribution, with p = {process_p}\n" + "*" * 50)
    else:
        print(f"Not a normal distribution, with p = {process_p}\n" + "*" * 50)

    print("Thread per socket:")
    print(f"Mean = {numpy.mean(thread_data)}")
    if normal_thread:
        print(f"Normal distribution, with p = {thread_p}\n" + "*" * 50)
    else:
        print(f"Not a normal distribution, with p = {thread_p}\n" + "*" * 50)

    ###################################################################################################################
    if normal_epoll and normal_process and normal_thread:
        # Hypotheses that all the data has normal distribution cannot be rejected
        # Performing Student t-test:
        t_stat1, p1 = stats.ttest_ind(epoll_data, process_data)
        t_stat2, p2 = stats.ttest_ind(epoll_data, thread_data)
        t_stat3, p3 = stats.ttest_ind(process_data, thread_data)

        # Displaying test results
        print("\nSTUDENT T-TEST\n" + "*" * 95)
        print(f"Epoll and Process per socket: t = {t_stat1} , p = {p1}\n" + "*" * 95)
        print(f"Epoll and Thread per socket: t = {t_stat2} , p = {p2}\n" + "*" * 95)
        print(f"Process per socket and Thread per socket: t = {t_stat3} , p = {p3}\n" + "*" * 95)

        # Checking if we have same distributions (testing null hypotheses)
        print("\nCOMPARING DISTRIBUTIONS\n" + "*" * 95)

        same_e_p = p1 >= alpha
        same_e_t = p2 >= alpha
        same_t_p = p3 >= alpha

        if same_e_p:
            print("We cannot reject hypotheses, that Epoll and Process per socket "
                  "are not significantly different \nfrom each other.\n" + "*" * 95)
        else:
            print("We reject hypotheses, that Epoll and Process per socket "
                  "are not significantly different \nfrom each other. (they are different, in other words)")
            print("Comparing means:")
            m1 = numpy.mean(epoll_data)
            m2 = numpy.mean(process_data)
            print(f"Epoll mean = {m1}")
            print(f"Process per socket mean = {m2}")
            if m1 < m2:
                print(f"Epoll has mean smaller by {100 - (m1 / m2) * 100}%\n" + "*" * 95)
            else:
                print(f"Process per socket has mean smaller by {100 - (m2 / m1) * 100}%\n" + "*" * 95)

        if same_e_t:
            print("We cannot reject hypotheses, that Epoll and Thread per socket "
                  "are not significantly different \nfrom each other.\n" + "*" * 95)
        else:
            print("We reject hypotheses, that Epoll and Thread per socket "
                  "are not significantly different \nfrom each other. (they are different, in other words)")
            print("Comparing means:")
            m1 = numpy.mean(epoll_data)
            m2 = numpy.mean(thread_data)
            print(f"Epoll mean = {m1}")
            print(f"Thread per socket mean = {m2}")
            if m1 < m2:
                print(f"Epoll has mean smaller by {100 - (m1 / m2) * 100}%\n" + "*" * 95)
            else:
                print(f"Thread per socket has mean smaller by {100 - (m2 / m1) * 100}%\n" + "*" * 95)

        if same_t_p:
            print("We cannot reject hypotheses, that Thread per socket and Process per socket "
                  "are not significantly \ndifferent from each other.\n" + "*" * 95)
        else:
            print("We reject hypotheses, that Thread per socket and Process per socket "
                  "are not significantly \ndifferent from each other. (they are different, in other words)")
            print("Comparing means:")
            m1 = numpy.mean(thread_data)
            m2 = numpy.mean(process_data)
            print(f"Thread per socket mean = {m1}")
            print(f"Process per socket mean = {m2}")
            if m1 < m2:
                print(f"Thread per socket has mean smaller by {100 - (m1 / m2) * 100}%\n" + "*" * 95)
            else:
                print(f"Process per socket has mean smaller by {100 - (m2 / m1) * 100}%\n" + "*" * 95)


    else:
        # Hypotheses that all the data has normal distribution can be rejected (or at least some of the data)
        # Performing Wilcoxon test:
        stat1, p1 = stats.wilcoxon(epoll_data, process_data)
        stat2, p2 = stats.wilcoxon(epoll_data, thread_data)
        stat3, p3 = stats.wilcoxon(process_data, thread_data)

        # Displaying test results
        print("\nWILCOXON TEST\n" + "*" * 95)
        print(f"Epoll and Process per socket: t = {stat1} , p = {p1}\n" + "*" * 95)
        print(f"Epoll and Thread per socket: t = {stat2} , p = {p2}\n" + "*" * 95)
        print(f"Process per socket and Thread per socket: t = {stat3} , p = {p3}\n" + "*" * 95)
