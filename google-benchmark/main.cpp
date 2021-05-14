#include <benchmark/benchmark.h>

#include <iostream>

#include "ThreadCrawler.h"

static void benchmark_thread_per_socket(benchmark::State& state) {
	std::vector<std::string> test_urls = {"http://www.example.com/",
					      "http://www.example.com/",
					      "http://www.example.com/"};

	for (auto _ : state) {
		state.PauseTiming();
		// preparing data if needed here
		state.ResumeTiming();

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

static void benchmark2(benchmark::State& state) {
	for (auto _ : state) {
		state.PauseTiming();
		// preparing data if needed here
		state.ResumeTiming();

		// тут
	}
}
// Register the function as a benchmark and passing an argument, number of
// iterations as a constraint
BENCHMARK(benchmark_thread_per_socket)->Iterations(1000);
//BENCHMARK(benchmark2)->Iterations(1000);
// Time in seconds, as a constraint
// BENCHMARK(BM_StringCreation)->Args({10, 0})->Arg(100)->Arg(1000)->MinTime(1);

BENCHMARK_MAIN();
