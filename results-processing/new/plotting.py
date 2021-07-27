import plotly.express as px
import plotly.graph_objects as go

BAR_WIDTH = 0.02

def create_histogram(distribution, filename):
    # Plot customizations
    custom_labels = {"x": "Time, s",
                     "y": "Number of iterations"}

    template = "plotly_white"
    # template = "simple_white"

    sample_histogram = px.histogram(x=distribution["data"],
                                    nbins=len(distribution["data"]) + 10,
                                    labels=custom_labels,
                                    template=template)
    sample_histogram.update_layout(
        font_size=20,
    )

    sample_histogram.update_xaxes(showline=True, linewidth=1, linecolor='black')
    sample_histogram.update_yaxes(showline=True, linewidth=1, linecolor='black')

    sample_histogram.write_image(filename)




def plot_distributions(distributions, filename):
    max_val = max([max(dist["data"]) for dist in distributions]) + 3
    fig = go.Figure()

    template = "plotly_white"
    # template = "simple_white"

    for dist in distributions:
        fig.add_trace(go.Histogram(
            x=dist["data"],
            name=dist["plot_name"],
            xbins=dict(
                start=0,
                end=max_val,
                size=BAR_WIDTH
            ),
            autobinx=False,
            marker_color=dist["color"],
            opacity=0.75
        ))

    fig.update_layout(
        xaxis_title_text='Time, s',
        yaxis_title_text='Count',
        bargap=0.2,
        bargroupgap=0.1,
        template=template,
        font_size=15,
        legend=dict(
            yanchor="top",
            y=0.99,
            xanchor="right",
            x=0.99
        )
    )

    fig.update_xaxes(showline=True, linewidth=1, linecolor='black')
    fig.update_yaxes(showline=True, linewidth=1, linecolor='black')

    fig.write_image(filename)

