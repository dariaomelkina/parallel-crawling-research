import numpy
import plotly.express as px
import plotly.graph_objects as go

if __name__ == "__main__":
    # Epoll for 264000 files
    threads_10 = [47.1791,
                  46.9795,
                  47.0385,
                  47.2885,
                  48.4375]
    threads_25 = [47.34,
                  47.6758,
                  47.3808,
                  47.6922]
    threads_50 = [47.058,
                  47.2129,
                  47.4319]
    threads_100 = [46.9527]

    sockets = [10,
               25,
               50,
               100,
               200]

    fig = go.Figure()
    fig.add_trace(go.Scatter(x=sockets, y=threads_10, name='10 threads'))
    fig.add_trace(go.Scatter(x=sockets, y=threads_25, name='25 threads'))
    fig.add_trace(go.Scatter(x=sockets, y=threads_50, name='50 threads'))
    fig.add_trace(go.Scatter(x=sockets, y=threads_100, name='100 threads'))

    template = "plotly_white"
    fig.update_layout(
        xaxis_title_text='Sockets per thread',
        yaxis_title_text='Time, s',
        template=template,
        font_size=15,
        legend=dict(
            yanchor="top",
            y=0.99,
            xanchor="left",
            x=0.01
        )
    )

    fig.update_xaxes(showline=True, linewidth=1, linecolor='black', type="linear", tickvals=sockets)
    fig.update_yaxes(showline=True, linewidth=1, linecolor='black', type="linear")
    fig.write_image("result-plots/epoll-comparison.pdf")

    # Process per socket for 264000 files
    pps_data = [63.103, 49.4304, 49.352, 49.3174, 49.4937, 49.4551, 49.7341]
    processes = [10, 50, 75, 100, 200, 300, 500]
    fig2 = go.Figure()
    fig2.add_trace(go.Scatter(x=processes, y=pps_data))

    template = "plotly_white"
    fig2.update_layout(
        xaxis_title_text='Number of processes',
        yaxis_title_text='Time, s',
        template=template,
        font_size=15,
    )

    fig2.update_xaxes(showline=True, linewidth=1, linecolor='black', type="linear", tickvals=processes)
    fig2.update_yaxes(showline=True, linewidth=1, linecolor='black')
    fig2.write_image("result-plots/pps-comparison.pdf")

    # Thread per socket for 264000 files
    tps_data = [62.7521, 48.9961, 48.7181, 48.6327, 48.4751, 48.3767, 48.2811, 48.241, 48.1638]
    threads = [10, 50, 75, 100, 200, 300, 500, 750, 1000]
    fig3 = go.Figure()
    fig3.add_trace(go.Scatter(x=threads, y=tps_data))

    template = "plotly_white"
    fig3.update_layout(
        xaxis_title_text='Number of threads',
        yaxis_title_text='Time, s',
        template=template,
        font_size=15,
    )
    # fig3.update_layout(yaxis_type="log")
    fig3.update_xaxes(showline=True, linewidth=1, linecolor='black', tickvals=threads)
    fig3.update_yaxes(showline=True, linewidth=1, linecolor='black')
    fig3.write_image("result-plots/tps-comparison.pdf")
