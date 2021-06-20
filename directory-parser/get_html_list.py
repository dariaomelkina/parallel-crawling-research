import os
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
import sys
import random


def density_plot(result_sizes):
    # Density Plot with Rug Plot
    ax = sns.distplot(result_sizes, hist=False, kde=True, rug=False,
                 color='darkblue',
                 kde_kws={'linewidth': 2},
                 rug_kws={'color': 'black'})

    plt.gcf().subplots_adjust(bottom=0.15)

    # plt.title('Density Plot of the size of html file in Kb')
    plt.xlabel('HTML size, Kb')
    plt.ylabel('Density')
    plt.xlim((0, max(result_sizes)))
    plt.xticks(np.linspace(0, max(result_sizes), num=5))

    ax.title.set_fontsize(18)
    x = ([ax.xaxis.label, ax.yaxis.label] +
             ax.get_xticklabels() + ax.get_yticklabels())
    ax.xaxis.label.set_fontsize(23)
    ax.yaxis.label.set_fontsize(18)
    for tick in ax.get_xticklabels():
        tick.set_fontsize(16)
    for tick in ax.get_yticklabels():
        tick.set_fontsize(13)

    # plt.show()
    plt.savefig('data_distribution_superbig.pdf')




def main():
    file_list = []

    # reading command line arguments:
    if len(sys.argv) not in (7, 8):
        print("Wrong number of system arguments. To get 0-25 percentile,")
        print("try sth like: python3 get_html_list.py 0 25 test-websites "
              "../google-benchmark/test.txt 10.42.0.1 plot=False")
        return
    db_directory, result_file, ip_address, multiplier, percentile_start, percentile_end = sys.argv[1:7]

    # recursively walking through all files:
    for subdir, dirs, files in os.walk(db_directory):
        for file in files:
            # print os.path.join(subdir, file)
            filepath = subdir + os.sep + file

            if filepath.endswith(".html"):
                file_stats = os.stat(filepath)
                # size of the file in Kilobytes
                file_size = file_stats.st_size / 1024
                # print(filepath, file_size)
                file_list.append((filepath, file_size))

    # sorting by the file_size
    file_list.sort(key=lambda x: x[1])

    # Deleting all files, that are bigger than 800 KB:

    index = 0
    for i in file_list:
        if i[1] >= 200:
            break
        index += 1
    file_list = file_list[:index]

    # calculating the start and end position in the sorted list
    start = len(file_list) * int(percentile_start) // 100
    end = len(file_list) * int(percentile_end) // 100

    # getting that percentile slice
    result = file_list[start:end]

    # Multiplicating the result list here:
    if int(multiplier) > 0:
        multiplier_list = []
        for _ in range(int(multiplier)):
            multiplier_list.extend(result.copy())
        result = multiplier_list

    # splitting array of tuples into two
    result_names = [i[0] for i in result]
    result_sizes = [i[1] for i in result]

    # combined_result_names = []
    # for i in range(10):
    #     for name in result_names:
    #         combined_result_names.append(name)

    df_describe = pd.DataFrame(result_sizes)
    print("The following stats, except for count, are in Kilobytes:", df_describe.describe())
    print("Total size of", len(result_sizes), "html files is", round(sum(result_sizes)), "Kb, or",
          round(sum(result_sizes) / 1024, 3), "Mb \n\n")

    # Shuffling randomly the names list:
    random.shuffle(result_names)

    with open(result_file, 'w') as write_file:
        for website in result_names:
            # print(website[14:])
            write_file.write("http://" + ip_address + '/' + website[14:] + '\n')

    if sys.argv[-1] == "plot=True":
        density_plot(result_sizes)


if __name__ == '__main__':
    main()
