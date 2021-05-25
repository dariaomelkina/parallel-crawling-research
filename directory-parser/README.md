#### If you want python to generate a specific percentile of website size and give statistics:

Execute the following from directory-parser directory:
```bash
python3 get_html_list.py db_directory result_file ip_address multiplier percentile_start percentile_end plot=False

# Or, in real world, to get 0-25 percentile, with each element repeating 2 times, and plotting, copy-paste the following:
python3 get_html_list.py test-websites ../google-benchmark/test.txt 10.42.0.150 2 0 25 plot=True

```
##### where:

test-websites - db_directory- directory to be parsed

../google-benchmark/test.txt  - result_file - dir to write the result

10.42.0.1 - ip address

2- multiplier - number of times, each file fill occur in the result_file

0, 25  - percentile_start and percentile_end. In this case it is 25% percentile.

plot=True or plot=False to plot the distribution of file sizes


#### Get the stats of files from the list of crawling html files
```bash
 python3.9 html_stats_from_file.py ../google-benchmark/test.txt test-webpages plot=True
 ```
##### where:
../google-benchmark/test.txt  - file with the list of urls in the form of http://10.42.0.1/wikipedia/Free_Software_Foundation.html

test-webpages - directory where the files from the above mentioned list could be found

plot=True or plot=False to plot the distribution of file sizes

#### Using C++

Example usage from that directory:
```bash
cmake -Bbuild && make -C ./build
./build/parser 192.168.0.107 ./sample ./test.txt
```
(executable, path to the directory for parsing, path to the output file)