import pandas as pd
from delete_outliers import delete_outliers, adjust_length


HEADER = "name,iterations,real_time,cpu_time,time_unit,bytes_per_second,items_per_second,label,error_occurred,error_message"
WARM_UP_NUM = 5

NAMES = {
    "benchmark_process_per_socket": "Process Per Socket",
    "benchmark_thread_per_socket": "Thread Per Socket",
    "benchmark_epoll": "Epoll",
}



def read_preprocess(filename, warm_up_num=WARM_UP_NUM):
    header_index = -1
    with open(filename) as f:
        for i, line in enumerate(f.readlines()):
            if line.strip() == HEADER:
                header_index = i
                break
    
    if header_index == -1:
        print("Invalid benchmark file")
        return 
    
    bad_rows = list(range(header_index)) + list(range(header_index + 1, header_index + 1 + warm_up_num))
    df = pd.read_csv(filename, skiprows=bad_rows)

    df = df[['name', 'real_time']]

    df['real_time'] /= 1_000_000_000

    def parse_name(row):
        tokens = row["name"].split("/")
        row["name"] = NAMES[tokens[0]]
        return row
    df = df.apply(parse_name, axis=1)

    dct = df.groupby('name')['real_time'].apply(delete_outliers).to_dict()
    for crawler in dct:
        if len(dct[crawler]) < 20:
            adjust_length(dct[crawler], 20)
    return dct

