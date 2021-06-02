#include <iostream>
#include <benchmark/benchmark.h>
#include "ThreadCrawler.h"
#include "ProcessCrawler.h"
#include "EpollCrawler.h"

static void benchmark_thread_per_socket(benchmark::State &state) {
    ThreadCrawler x = ThreadCrawler(state.range(1));

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
    ProcessCrawler x = ProcessCrawler(state.range(1));

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

    EpollCrawler x = EpollCrawler(state.range(1), state.range(2));
    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt", state.range(0));
        x.start_workers();
        state.ResumeTiming();

        // processing links
        x.process_queue();
    }
}

int iters = 5;
// int args = 132859;
int args = 300000;

int args_small = 30000;
int args_rozigriv = 10000;

// Examples of usage:
// BENCHMARK(benchmark_epoll)->Args({args, 10, 15})->Iterations(1);
// BENCHMARK(benchmark_process_per_socket)->Args({args, 10})->Iterations(iters);
// BENCHMARK(benchmark_thread_per_socket)->Args({args, 10})->Iterations(iters);


BENCHMARK(benchmark_epoll)
    ->Args({args_rozigriv, 10, 10})
    ->Iterations(2);

// first argument in epol is number of workers, second- max_requests
BENCHMARK(benchmark_epoll)
    ->Args({args_rozigriv, 10, 10})
    ->Args({args_rozigriv, 10, 50})
    ->Args({args_rozigriv, 10, 100})
    ->Args({args_rozigriv, 10, 200})
    ->Args({args_rozigriv, 10, 500})

    ->Args({args_rozigriv, 25, 10})
    ->Args({args_rozigriv, 25, 50})
    ->Args({args_rozigriv, 25, 100})
    ->Args({args_rozigriv, 25, 200})

    ->Args({args_rozigriv, 50, 10})
    ->Args({args_rozigriv, 50, 50})
    ->Args({args_rozigriv, 50, 100})

    ->Iterations(iters);




// Time in seconds, as a constraint
// BENCHMARK(benchmark_epoll)->Range(16, 4<<10)->Iterations(5);
// BENCHMARK(BM_StringCreation)->Args({10, 0})->Arg(100)->Arg(1000)->MinTime(1);

BENCHMARK_MAIN();
