import os
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
import sys
import random


def density_plot(result_sizes):
    # Density Plot with Rug Plot
    sns.distplot(result_sizes, hist=False, kde=True, rug=True,
                 color='darkblue',
                 kde_kws={'linewidth': 2},
                 rug_kws={'color': 'black'})

    # Plot formatting
    plt.title('Density Plot of the size of html file in Kb')
    plt.xlabel('HTML size, Kb')
    plt.ylabel('Density')
    plt.xlim((0, max(result_sizes)))
    plt.xticks(np.linspace(0, max(result_sizes), num=11))
    plt.show()


def main():
    file_list = []

    # reading command line arguments:
    if len(sys.argv) not in (6, 7):
        print("Wrong number of system arguments. To get 0-25 percentile,")
        print("try sth like: python3 get_html_list.py 0 25 test-websites "
              "../google-benchmark/test.txt 10.42.0.1 plot=False")
        return
    percentile_start, percentile_end, db_directory, result_file, ip_address = sys.argv[1:6]
    print(percentile_start, percentile_end, db_directory, result_file, ip_address)

    # recursively walking through all files:
    for subdir, dirs, files in os.walk(db_directory):
        for file in files:
            # print os.path.join(subdir, file)
            filepath = subdir + os.sep + file

            if filepath.endswith(".html"):
                file_stats = os.stat(filepath)
                # size of the file in Kilobytes
                file_size = round(file_stats.st_size / 1024)
                # print(filepath, file_size)
                file_list.append((filepath, file_size))

    # sorting by the file_size
    file_list.sort(key=lambda x: x[1])

    # calculating the start and end position in the sorted list
    start = len(file_list) * int(percentile_start) // 100
    end = len(file_list) * int(percentile_end) // 100

    # getting that percentile slice
    result = file_list[start:end]

    # splitting array of tuples into two
    result_names = [i[0] for i in result]
    result_sizes = [i[1] for i in result]


    combined_result_names = []
    for i in range(10):
        for name in result_names:
            combined_result_names.append(name)

    df_describe = pd.DataFrame(combined_result_names)
    print("The following stats, except for count, are in Kilobytes:", df_describe.describe())
    # print("Total size of", len(combined_result_names), "html files is", sum(combined_result_names), "Kb")

    # print(combined_result_names[:5])
    random.shuffle(combined_result_names)
    # print(combined_result_names[:5])
    # print(len(combined_result_names))
    # print(len(result_names))

    with open(result_file, 'w') as write_file:
        for website in combined_result_names:
            # print(website[14:])
            write_file.write("http://" + ip_address + '/' + website[14:] + '\n')

    if sys.argv[-1] == "plot=True":
        density_plot(combined_result_names)


if __name__ == '__main__':
    main()
