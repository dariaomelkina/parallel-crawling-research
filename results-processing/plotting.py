import numpy
import plotly.express as px
import plotly.graph_objects as go


def create_histograms(distributions):
    # Plot customizations
    custom_labels = {"x": "Time, s",
                     "y": "Number of iterations"}

    for distribution in distributions:
        name = distribution["name"]
        sample_histogtam = px.histogram(x=distribution["data"],
                                nbins=50,
                                title=f"{name} results distribution",
                                labels=custom_labels)

        sample_histogtam.write_image(f"result-plots/{name}-distribution.png")


def display_normality_test(dist_dict):
    # Displaying normality results
    name = dist_dict["name"]
    data = dist_dict["data"]
    p_value = dist_dict["p_value"]

    print("NORMALITY TESTING\n" + "*" * 50)
    print(f"{name}:")
    print(f"Mean = {round(numpy.mean(data), 2)}")

    if dist_dict["is_normal"]:
        print(f"Normal distribution, with p = {'%.2g' % p_value}\n" + "*" * 50)
    else:
        print(f"Not a normal distribution, with p = {'%.2g' % p_value}\n" + "*" * 50)


def three_distributions_plot(epoll_data, process_data, thread_data):
    # Three crawlers together on one plot
    max_val = max(max(epoll_data), max(process_data), max(thread_data)) + 3
    fig = go.Figure()

    plot_data = (
        {"data": epoll_data, "name": "epol", "color": "steelblue"},
        {"data": process_data, "name": "process per socket", "color": "blueviolet"},
        {"data": thread_data, "name": "thread per socket", "color": "deeppink"}
    )

    for distr in plot_data:
        fig.add_trace(go.Histogram(
            x=distr["data"],
            name=distr["name"],
            xbins=dict(
                start=0,
                end=max_val,
                size=0.01,
            ),
            autobinx=False,
            marker_color=distr["color"],
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

