#include <iostream>
#include <benchmark/benchmark.h>
#include "ThreadSocketCrawler.h"
#include "ThreadCrawler.h"
#include "ProcessCrawler.h"
#include "EpollCrawler.h"
#include "ProcessSocketCrawler.h"





static void benchmark_thread(benchmark::State& state) {
    ThreadCrawler x = ThreadCrawler(4);
	for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt");
        state.ResumeTiming();
		// processing links
		x.process_queue();
	}
}

static void benchmark_thread_per_socket(benchmark::State& state) {
    ThreadSocketCrawler x = ThreadSocketCrawler(4);
    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt");
        state.ResumeTiming();
        // processing links
        x.process_queue();
    }
}

static void benchmark_process_per_socket(benchmark::State& state) {
    ProcessSocketCrawler x = ProcessSocketCrawler(4);

    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt");
        state.ResumeTiming();
        // processing links
        x.process_queue();
    }
}



static void benchmark_process(benchmark::State& state) {
    ProcessCrawler x = ProcessCrawler(4);

	for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt");
        state.ResumeTiming();
		// processing links
		x.process_queue();
	}
}

static void benchmark_epoll(benchmark::State& state) {
    EpollCrawler x = EpollCrawler(4, 4);
    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt");
        state.ResumeTiming();
        // processing links
        x.process_queue();
    }
}

// Register the function as a benchmark and passing an argument, number of
// iterations as a constraint
BENCHMARK(benchmark_thread_per_socket)->Iterations(1);
BENCHMARK(benchmark_thread)->Iterations(1);
BENCHMARK(benchmark_process_per_socket)->Iterations(1);
BENCHMARK(benchmark_process)->Iterations(1);
BENCHMARK(benchmark_epoll)->Iterations(1);

//BENCHMARK(benchmark_thread_per_socket)->Iterations(10)->Arg(3);
//BENCHMARK(benchmark_thread_per_socket)->Iterations(10)->Arg(4);
//BENCHMARK(benchmark_thread_per_socket)->Iterations(10)->Arg(5);
//BENCHMARK(benchmark_process_per_socket)->Iterations(1000);
// Time in seconds, as a constraint
// BENCHMARK(BM_StringCreation)->Args({10, 0})->Arg(100)->Arg(1000)->MinTime(1);

BENCHMARK_MAIN();
