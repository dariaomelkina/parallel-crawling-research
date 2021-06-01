#include <iostream>
#include <benchmark/benchmark.h>
#include "ThreadCrawler.h"
#include "ProcessCrawler.h"
#include "EpollCrawler.h"

static void benchmark_thread_per_socket_10(benchmark::State &state) {
    ThreadCrawler x = ThreadCrawler(10);
    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt", state.range(0));
        x.start_workers();
        state.ResumeTiming();
        // processing links
        x.process_queue();
    }
}

static void benchmark_thread_per_socket_100(benchmark::State &state) {
    ThreadCrawler x = ThreadCrawler(100);
    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt", state.range(0));
        x.start_workers();
        state.ResumeTiming();
        // processing links
        x.process_queue();
    }
}

static void benchmark_thread_per_socket_500(benchmark::State &state) {
    ThreadCrawler x = ThreadCrawler(500);
    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt", state.range(0));
        x.start_workers();
        state.ResumeTiming();
        // processing links
        x.process_queue();
    }
}

static void benchmark_thread_per_socket_1000(benchmark::State &state) {
    ThreadCrawler x = ThreadCrawler(1000);
    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt", state.range(0));
        x.start_workers();
        state.ResumeTiming();
        // processing links
        x.process_queue();
    }
}

static void benchmark_thread_per_socket_2000(benchmark::State &state) {
    ThreadCrawler x = ThreadCrawler(1000);
    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt", state.range(0));
        x.start_workers();
        state.ResumeTiming();
        // processing links
        x.process_queue();
    }
}



static void benchmark_process_per_socket(benchmark::State &state) {
    ProcessCrawler x = ProcessCrawler(1000);

    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt", state.range(0));
        x.start_workers();
        state.ResumeTiming();

        // processing links
        x.process_queue();
    }
}

static void benchmark_epoll(benchmark::State &state) {
    EpollCrawler x = EpollCrawler(30, 125);
    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt", state.range(0));
        x.start_workers();
        state.ResumeTiming();

        // processing links
        x.process_queue();
    }
}

// Register the function as a benchmark and passing an argument, number of
// iterations as a constraint
int iters = 5;
int args = 132859;

int args_small = 30000;
int args_rozigriv = 10000;

// BENCHMARK(benchmark_thread_per_socket)->Arg(args)->Iterations(1);
// BENCHMARK(benchmark_process_per_socket)->Arg(args)->Iterations(1);
// BENCHMARK(benchmark_thread_per_socket)->Arg(args)->Iterations(1);


BENCHMARK(benchmark_process_per_socket)->Arg(args)->Iterations(1);

// BENCHMARK(benchmark_thread_per_socket_10)->Arg(args)->Iterations(4);
// BENCHMARK(benchmark_thread_per_socket_100)->Arg(args)->Iterations(4);
// BENCHMARK(benchmark_thread_per_socket_2000)->Arg(args)->Iterations(4);

// BENCHMARK(benchmark_thread_per_socket_1000)->Arg(args)->Iterations(4);

// BENCHMARK(benchmark_thread_per_socket_2000)->Arg(args)->Iterations(4);


// BENCHMARK(benchmark_process_per_socket)->Arg(args)->Iterations(iters);
// BENCHMARK(benchmark_thread_per_socket)->Arg(args)->Iterations(iters);
// BENCHMARK(benchmark_epoll)->Arg(args)->Iterations(iters);


// BENCHMARK(benchmark_epoll)->Range(16, 4<<10)->Iterations(5);


// Time in seconds, as a constraint
// BENCHMARK(BM_StringCreation)->Args({10, 0})->Arg(100)->Arg(1000)->MinTime(1);

BENCHMARK_MAIN();
