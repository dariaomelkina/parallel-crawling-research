import sys
import pandas as pd
import plotly.graph_objects as go
import plotly.express as px

NUMBER_OF_PARAMETER_ROWS = 9
NUMBER_OF_WARNING_ROWS = 1

if __name__ == "__main__":
    file = sys.argv[1]
    data = pd.read_csv(file, skiprows=range(0, NUMBER_OF_PARAMETER_ROWS + NUMBER_OF_WARNING_ROWS))

    # Table with general data
    general_parameters = pd.read_csv(file, names=["parameters"], nrows=NUMBER_OF_PARAMETER_ROWS)
    table = go.Figure(data=[go.Table(header=dict(values=list(general_parameters.columns),
                                                 fill_color='paleturquoise',
                                                 align='left'),
                                     cells=dict(values=[general_parameters.parameters],
                                                fill_color='lavender',
                                                align='left'))])
    table.write_image("result_plots/parameters.png")

    # Plots for different number of iterations (real time)
    data[['crawler', 'websites', 'additional_iterations']] = data.name.str.split("/", expand=True)

    colorsIdx = {'benchmark_epoll': 'epoll', 'benchmark_process_per_socket': 'process per socket',
                 'benchmark_thread_per_socket': 'thread per socket'}
    cols = data[data["iterations"] == 5]['crawler'].map(colorsIdx)

    fig1 = px.line(data[data["iterations"] == 5], x="websites", y="real_time", title='Real Time plot for 5 iterations',
                   color=cols,
                   labels={"color": "Crawler:",
                           "real_time": "real time (ns)",
                           "websites": "number of crawled websites"})
    fig1.write_image("result_plots/real_time.png")

    # Plots for different number of iterations (cpu time)
    fig2 = px.line(data[data["iterations"] == 5], x="websites", y="cpu_time", title='CPU Time plot for 5 iterations',
                   color=cols,
                   labels={"color": "Crawler:",
                           "cpu_time": "cpu time (ns)",
                           "websites": "number of crawled websites"})
    fig2.write_image("result_plots/cpu_time.png")