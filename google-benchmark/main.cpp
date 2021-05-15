#include <iostream>

#include <benchmark/benchmark.h>
#include "ThreadCrawler.h"
#include "ProcessCrawler.h"

static void benchmark_thread_per_socket(benchmark::State& state) {
	std::vector<std::string> test_urls = {"http://www.example.com",
					      "http://www.example.com",
					      "http://www.example.com"};

	for (auto _ : state) {
		ThreadCrawler x = ThreadCrawler(4);

		// adding links to the crawler
		for (auto& url : test_urls) {
			std::cout << url << std::endl;
			x.add_url(url);
		}

		// processing links
		x.process_queue();
	}
}

static void benchmark_process_per_socket(benchmark::State& state) {
	std::vector<std::string> test_urls = {"http://www.example.com",
					      "http://www.example.com",
					      "http://www.example.com"};

	for (auto _ : state) {
		ProcessCrawler x = ProcessCrawler(4);

		// adding links to the crawler
		for (auto& url : test_urls) {
			std::cout << url << std::endl;
			x.add_url(url);
		}

		// processing links
		x.process_queue();
	}
}

// Register the function as a benchmark and passing an argument, number of
// iterations as a constraint
BENCHMARK(benchmark_thread_per_socket)->Iterations(1000);
BENCHMARK(benchmark_process_per_socket)->Iterations(1000);
// Time in seconds, as a constraint
// BENCHMARK(BM_StringCreation)->Args({10, 0})->Arg(100)->Arg(1000)->MinTime(1);

BENCHMARK_MAIN();
