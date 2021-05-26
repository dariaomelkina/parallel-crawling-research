import os
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
import sys


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
    file_sizes = []

    # reading command line arguments:
    if len(sys.argv) not in (3, 4):
        print("Wrong number of system arguments. To get 0-25 percentile,")
        print("try sth like:")
        print("python3 html_stats_from_file.py ../google-benchmark/test.txt "
              "test-websites plot=False")
        return
    input_file, db_directory = sys.argv[1:3]
    print(input_file, db_directory)

    # recursively walking through all files:
    with open(input_file, 'r') as file:
        # cutting the 'http://10.42.0.1/' from the path:
        for line in file:
            line = line.strip()
            slash_count, index = 0, 0
            while slash_count < 3 and index != len(line):
                if line[index] == '/':
                    slash_count += 1
                index += 1
            filepath = line[index:]
            print(filepath)

            # opening the file stats, and saving the size of the file to list
            file_stats = os.stat(db_directory + '/' + filepath)
            file_sizes.append(file_stats.st_size / 1024)

    print(file_sizes)
    # sorting by the file_size
    # file_list.sort(key=lambda x: x[1])

    df_describe = pd.DataFrame(file_sizes)
    print("The following stats, except for count, are in Kilobytes:", df_describe.describe())
    print("Total size of", len(file_sizes), "html files is", sum(file_sizes), "Kb")

    if sys.argv[-1] == "plot=True":
        density_plot(file_sizes)


if __name__ == '__main__':
    main()
