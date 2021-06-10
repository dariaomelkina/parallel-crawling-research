import plotly.graph_objects as go
import pandas as pd


def parse_iteration(iteration):
    split = iteration.split('/')
    if len(split) > 4:
        name, files_num, threads, sockets_thread, _ = split
        return name, int(files_num), int(threads), int(sockets_thread)
    else:
        name, files_num, threads, _ = split
        return name, int(files_num), int(threads), 0


def sort_by_value(threads, means):
    sorted_means = [x for _, x in sorted(zip(threads, means), key=lambda pair: pair[0])]
    sorted_threads = sorted(threads)
    return sorted_threads, sorted_means


def read_csv(path):
    df = pd.read_csv(path)

    results_dict = {
        "benchmark_epoll": [],
        "benchmark_process_per_socket": [],
        "benchmark_thread_per_socket": []
    }
    for index, row in df.iterrows():
        name, files_num, threads, sockets_thread = parse_iteration(row['name'])
        mean = float(row['mean'])
        std = float(row['std'])
        to_append = {
            "mean": mean,
            "std": std,
            "threads": threads,
            "sockets_thread": sockets_thread
        }
        results_dict[name].append(to_append)
    return results_dict


def plot(results_dict):
    for crawler in results_dict.keys():
        means = []
        threads = []
        sockets = []
        for measurement in results_dict[crawler]:
            means.append(measurement['mean'])
            threads.append(measurement['threads'])
            sockets.append(measurement['sockets_thread'])

        if crawler == "benchmark_process_per_socket" or crawler == "benchmark_thread_per_socket":
            # sorting because data from dict is unordered
            threads, means = sort_by_value(threads, means)

            # Thread per socket for 264000 files
            fig3 = go.Figure()
            fig3.add_trace(go.Scatter(x=threads, y=means))

            template = "plotly_white"
            fig3.update_layout(
                xaxis_title_text='Number of threads',
                yaxis_title_text='Time, s',
                template=template,
                font_size=15,
            )
            # fig3.update_layout(yaxis_type="log")
            # fig3.update_xaxes(showline=True, linewidth=1, linecolor='black', tickvals=threads)
            fig3.update_xaxes(showline=True, linewidth=1, linecolor='black')
            fig3.update_yaxes(showline=True, linewidth=1, linecolor='black')
            fig3.write_image(f"result-plots/{crawler}.pdf")

        if crawler == "benchmark_epoll":
            threads_unique = sorted(list(set(threads)))

            fig = go.Figure()

            # plotting a single for each thread number, it just works
            for threads_num in threads_unique:
                length = len(sockets)
                means_thread = [means[i] for i in range(length) if threads[i] == threads_num]
                sockets_thread = [sockets[i] for i in range(length) if threads[i] == threads_num]

                sockets_thread, means_thread = sort_by_value(sockets_thread, means_thread)
                fig.add_trace(go.Scatter(x=sockets_thread, y=means_thread, name=f"{threads_num} threads"))

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
            fig.write_image(f"result-plots/{crawler}.pdf")


def main():
    means_std_filepath = "mean_std.csv"
    results_dict = read_csv(means_std_filepath)
    plot(results_dict)


if __name__ == "__main__":
    main()
