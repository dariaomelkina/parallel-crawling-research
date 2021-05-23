#include <iostream>
#include <benchmark/benchmark.h>
#include "ThreadSocketCrawler.h"
#include "ThreadCrawler.h"
#include "ProcessCrawler.h"
#include "EpollCrawler.h"
#include "ProcessSocketCrawler.h"


<<<<<<< HEAD



static void benchmark_thread(benchmark::State& state) {
    ThreadCrawler x = ThreadCrawler(4);
=======
static void benchmark_thread_per_socket(benchmark::State& state) {
    ThreadCrawler x = ThreadCrawler(8);
    x.add_from_file("../test.txt", state.range(0));

>>>>>>> 11b2c3b88acedea84a84bf4ee3d174c0d6c216a3
	for (auto _ : state) {
        // state.PauseTiming();
        // state.ResumeTiming();
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
<<<<<<< HEAD
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
=======
    ProcessCrawler x = ProcessCrawler(8);
    x.add_from_file("../test.txt", state.range(0));
>>>>>>> 11b2c3b88acedea84a84bf4ee3d174c0d6c216a3

	for (auto _ : state) {
		// processing links
		x.process_queue();
	}
}

static void benchmark_epoll(benchmark::State& state) {
<<<<<<< HEAD
    EpollCrawler x = EpollCrawler(4, 4);
=======
    EpollCrawler x = EpollCrawler(8, 2000);
    x.add_from_file("../test.txt", state.range(0));

>>>>>>> 11b2c3b88acedea84a84bf4ee3d174c0d6c216a3
    for (auto _ : state) {
        // processing links
        x.process_queue();
    }
}

// Register the function as a benchmark and passing an argument, number of
// iterations as a constraint
<<<<<<< HEAD
BENCHMARK(benchmark_thread_per_socket)->Iterations(1);
BENCHMARK(benchmark_thread)->Iterations(1);
BENCHMARK(benchmark_process_per_socket)->Iterations(1);
BENCHMARK(benchmark_process)->Iterations(1);
BENCHMARK(benchmark_epoll)->Iterations(1);
=======
BENCHMARK(benchmark_epoll)->Range(16, 2<<10)->Iterations(1);

// BENCHMARK(benchmark_epoll)->Arg(1000)->Iterations(6);
// BENCHMARK(benchmark_thread_per_socket)->Arg(1000)->Iterations(6);
// BENCHMARK(benchmark_process_per_socket)->Arg(1000)->Iterations(6);
// BENCHMARK(benchmark_thread_per_socket)->Arg(1000)->Iterations(6);
>>>>>>> 11b2c3b88acedea84a84bf4ee3d174c0d6c216a3

//BENCHMARK(benchmark_thread_per_socket)->Iterations(10)->Arg(3);
//BENCHMARK(benchmark_thread_per_socket)->Iterations(10)->Arg(4);
//BENCHMARK(benchmark_thread_per_socket)->Iterations(10)->Arg(5);
//BENCHMARK(benchmark_process_per_socket)->Iterations(1000);
// Time in seconds, as a constraint
// BENCHMARK(BM_StringCreation)->Args({10, 0})->Arg(100)->Arg(1000)->MinTime(1);

BENCHMARK_MAIN();
