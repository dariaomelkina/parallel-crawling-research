# TODO: there should be used "load average" unit
#  check for better metrics or their description (number of websites -->> bytes ?)
#  add info on the webpage sizes
#  or use two datasets of webpages as constants (there will be their full descriptions in the paper “сумарний розмір
#  такий то, кількість файлів така то, медіанний розмір такий то, середнє квадратичне по розміру таке то”)
#

import sys
import pandas as pd
import plotly.graph_objects as go
import plotly.express as px

NUMBER_OF_PARAMETER_ROWS = 9
NUMBER_OF_WARNING_ROWS = 1
ITERATIONS = 5
NAME_PARAMETER = 'ethernet'

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
    table.write_image(f"result_plots/{NAME_PARAMETER}_parameters.png")

    # Plots for different number of iterations (real time)
    data[['crawler', 'websites', 'additional_iterations']] = data.name.str.split("/", expand=True)
    data['cpu_time'] = data['cpu_time'] / 1000000000
    data['real_time'] = data['real_time'] / 1000000000

    colorsIdx = {'benchmark_epoll': 'epoll', 'benchmark_process_per_socket': 'process per socket',
                 'benchmark_thread_per_socket': 'thread per socket'}
    cols = data[data["iterations"] == ITERATIONS]['crawler'].map(colorsIdx)

    fig1 = px.line(data[data["iterations"] == ITERATIONS], x="websites", y="real_time",
                   title=f'Real Time plot for {ITERATIONS} iterations ({NAME_PARAMETER})',
                   color=cols,
                   labels={"color": "Crawler:",
                           "real_time": "real time (s)",
                           "websites": "number of crawled websites"})
    fig1.update_xaxes(type='linear')
    fig1.write_image(f"result_plots/{NAME_PARAMETER}_real_time.png")

    # Plots for different number of iterations (cpu time)
    fig2 = px.line(data[data["iterations"] == ITERATIONS], x="websites", y="cpu_time",
                   title=f'CPU Time plot for {ITERATIONS} iterations ({NAME_PARAMETER})',
                   color=cols,
                   labels={"color": "Crawler:",
                           "cpu_time": "cpu time (s)",
                           "websites": "number of crawled websites"})
    fig2.update_xaxes(type='linear')
    fig2.write_image(f"result_plots/{NAME_PARAMETER}_cpu_time.png")
