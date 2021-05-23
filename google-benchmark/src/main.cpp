#include <iostream>
#include <benchmark/benchmark.h>
#include "ThreadSocketCrawler.h"
#include "ThreadCrawler.h"
#include "ProcessCrawler.h"
#include "EpollCrawler.h"
#include "ProcessSocketCrawler.h"




static void benchmark_thread_per_socket(benchmark::State& state) {
    ThreadCrawler x = ThreadCrawler(16);
	for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt", state.range(0));
        state.ResumeTiming();
		// processing links
		x.process_queue();

	}
}


static void benchmark_process_per_socket(benchmark::State& state) {
    ProcessCrawler x = ProcessCrawler(16);

	for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt", state.range(0));
        state.ResumeTiming();

		// processing links
		x.process_queue();
	}
}

static void benchmark_epoll(benchmark::State& state) {
    EpollCrawler x = EpollCrawler(4, 10000);
    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt", state.range(0));
        state.ResumeTiming();

        // processing links
        x.process_queue();
    }
}

// Register the function as a benchmark and passing an argument, number of
// iterations as a constraint
BENCHMARK(benchmark_process_per_socket)->Arg(100)->Iterations(1);
BENCHMARK(benchmark_thread_per_socket)->Arg(100)->Iterations(1);
BENCHMARK(benchmark_epoll)->Arg(100)->Iterations(1);

int iters = 3;
int args = 2000;

// BENCHMARK(benchmark_epoll)->Arg(args)->Iterations(iters);
// BENCHMARK(benchmark_thread_per_socket)->Arg(args)->Iterations(iters);
// BENCHMARK(benchmark_epoll)->Arg(args)->Iterations(iters);


// BENCHMARK(benchmark_epoll)->Range(16, 4<<10)->Iterations(5);
// BENCHMARK(benchmark_process_per_socket)->Range(16, 4<<10)->Iterations(5);
// BENCHMARK(benchmark_thread_per_socket)->Range(16, 4<<10)->Iterations(5);
// BENCHMARK(benchmark_process_per_socket)->Range(16, 4<<10)->Iterations(5);
// BENCHMARK(benchmark_epoll)->Range(16, 4<<10)->Iterations(5);



// Time in seconds, as a constraint
// BENCHMARK(BM_StringCreation)->Args({10, 0})->Arg(100)->Arg(1000)->MinTime(1);

BENCHMARK_MAIN();
