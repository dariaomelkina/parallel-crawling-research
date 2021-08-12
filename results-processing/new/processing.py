import sys

from plotting import plot_distributions, create_histogram
from statistical_tests import display_normality_test, compare_distributions
from preprocessing import read_preprocess, NAMES


COLORS = ["darkgreen", "red", "darkblue", "orange", "black"]
RESULT_FOLDER = "results"



def one_file_processing(filename):
    data = read_preprocess(filename)

    distributions = [{
        "crawler_type": name,
        "name": name,
        "data": data[name],
        "color": COLORS[i],
        "plot_name": name
        } for i, name in enumerate(data)]

    parsed_filename = filename.split('.')[0].split('/')[-1].replace('_', '-')

    for dist in distributions:
        display_normality_test(dist)
        create_histogram(dist, RESULT_FOLDER +
         f"/{'-'.join(dist['crawler_type'].lower().split())}-{parsed_filename}-distribution.pdf")
    
    for i in range(len(distributions)):
        for j in range(i+1, len(distributions)):
            compare_distributions(distributions[i], distributions[j])
    
    plot_distributions(distributions, RESULT_FOLDER + f"/all-crawlers-{parsed_filename}.pdf")


def many_files_processing(filenames):
    crawlers = {name: [] for name in NAMES.values()}
    for filename in filenames:
        data = read_preprocess(filename)
        parsed_filename = filename.split('/')[-1].split('.')[0].replace('_', ', ')
        distributions = [{
            "crawler_type": name,
            "name": f"{name} ({parsed_filename})",
            "data": data[name],
            "plot_name": parsed_filename
            } for i, name in enumerate(data)]
        for dist in distributions:
            crawlers[dist["crawler_type"]].append(dist)

    
    for crawler_type, distributions in crawlers.items():
        print(crawler_type)
        for i, dist in enumerate(distributions):
            display_normality_test(dist)
            dist['color'] = COLORS[i]


        for i in range(len(distributions)):
            for j in range(i+1, len(distributions)):
                compare_distributions(distributions[i], distributions[j])
        
        print("\n\n")
    
        plot_distributions(distributions, RESULT_FOLDER + f"/all-files-{crawler_type.lower().replace(' ', '-')}.pdf")



def main():
    if len(sys.argv) == 1:
        print("Enter at least one filename")
    elif len(sys.argv) == 2:
        one_file_processing(sys.argv[1])
    elif len(COLORS) + 1 >= len(sys.argv) > 2:
        many_files_processing(sys.argv[1:])
    else:
        print("Too many files to process. (You need to add more colors to the COLORS list)")


if __name__ == "__main__":
    main()



