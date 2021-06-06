import sys
import pandas as pd
import plotly.express as px
import plotly.graph_objects as go
from scipy import stats
import numpy
from delete_outliers import delete_outliers

NUMBER_OF_PARAMETER_ROWS = 0  # First lines without needed data
# NUMBER_OF_WARNING_ROWS = 20
NUMBER_Of_SKIP_ROWS = 0

if __name__ == "__main__":
    ###################################################################################################################
    # Read csv files
    df = pd.read_csv(sys.argv[1],
                     skiprows=range(0, NUMBER_OF_PARAMETER_ROWS))

    data_real_time = df['real_time'][NUMBER_Of_SKIP_ROWS:] / 10 ** 9
    data_cpu_time = df['cpu_time'][NUMBER_Of_SKIP_ROWS:] / 10 ** 9
    ###################################################################################################################
    # Delete outliers
    data_real_time = delete_outliers(data_real_time)
    data_cpu_time = delete_outliers(data_cpu_time)

    ###################################################################################################################
    # Display statistics
    print(f"For {sys.argv[1]}:\n")
    print("\tStatistics for real time, in seconds")
    print(pd.Series(data_real_time).describe())
    print("\n\tStatistics for CPU time, in seconds")
    print(pd.Series(data_cpu_time).describe())

    ###################################################################################################################
    # Testing normality
    print("\nTesting normality:\n")

    alpha = 1e-3
    k2, p = stats.normaltest(data_real_time)
    normal_data = p >= alpha

    print(f"Mean = {round(numpy.mean(data_real_time), 2)}")

    if normal_data:
        print(f"Normal distribution, with p = {'%.2g' % p}\n")
    else:
        print(f"Not a normal distribution, with p = {'%.2g' % p}\n")

    ###################################################################################################################
    # Plot customizations
    custom_labels = {"x": "Time, s",
                     "y": "Number of iterations"}

    ###################################################################################################################
    # Plot moving average

    window_size = 5
    numbers_series = pd.Series(data_real_time)
    windows = numbers_series.rolling(window_size)
    moving_averages = windows.mean()
    moving_averages_list = moving_averages.tolist()
    without_nans = moving_averages_list[window_size - 1:]

    fig_ma = go.Figure()
    fig_ma.add_trace(go.Scatter(x=[i for i in range(len(without_nans))], y=without_nans,
                                mode='lines',
                                name=f'moving average ({window_size} iterations)'))

    fig_ma.add_trace(go.Scatter(x=[i for i in range(len(data_real_time))], y=data_real_time,
                                mode='lines',
                                name='real time for each iteration'))

    fig_ma.update_layout(title=f'For {sys.argv[1]}',
                         xaxis_title='real time',
                         yaxis_title='iteration')

    fig_ma.show()

    ###################################################################################################################
    # Creating bar plot of the distribution
    fig = px.histogram(x=data_real_time,
                       nbins=len(data_real_time) + 3,
                       title=f"Results distribution of {sys.argv[1]} (real time)",
                       labels=custom_labels)

    # Uncomment if You want to save graph
    # fig.write_image("result-plots/test-plot.png")
    # fig.show()
