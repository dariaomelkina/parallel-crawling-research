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

static void benchmark_thread_per_socket_barier(benchmark::State &state) {
    ThreadCrawler x = ThreadCrawler(state.range(1));

    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt", state.range(0));
        state.ResumeTiming();

        x.start_workers();
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

static void benchmark_process_per_socket_barier(benchmark::State &state) {
    ProcessCrawler x = ProcessCrawler(state.range(1));

    for (auto _ : state) {
        state.PauseTiming();
        x.add_from_file("../test.txt", state.range(0));
        state.ResumeTiming();

        x.start_workers();
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

static void hlam(benchmark::State &state) {

    EpollCrawler x = EpollCrawler(state.range(1), state.range(2));
    for (auto _ : state) {
        int x = 0;
        for (size_t i = 0; i < 10000; i++)
        {
            x++;
        }
        
    }
}

int iters = 1;
int args = 264000;

int args_small = 30000;
int args_rozigriv = 20000;

// Rozigriv:

BENCHMARK(benchmark_process_per_socket)->Args({args, 100})->Iterations(1);
// BENCHMARK(benchmark_thread_per_socket)->Args({args, 100})->Iterations(1);
// BENCHMARK(benchmark_process_per_socket)->Args({args, 100})->Iterations(1);
// BENCHMARK(benchmark_thread_per_socket)->Args({args, 100})->Iterations(1);









// BENCHMARK(benchmark_process_per_socket)
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})
//     ->Args({args, 100})

//     ->Iterations(1);

// BENCHMARK(benchmark_thread_per_socket)
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})
//     ->Args({args, 1000})

//     ->Iterations(1);

// BENCHMARK(benchmark_epoll)
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
//      ->Args({args, 10, 25})
     
//     ->Iterations(1);



// first argument in epol is number of workers, second- max_requests

// Time in seconds, as a constraint
// BENCHMARK(benchmark_epoll)->Range(16, 4<<10)->Iterations(5);
// BENCHMARK(BM_StringCreation)->Args({10, 0})->Arg(100)->Arg(1000)->MinTime(1);

BENCHMARK_MAIN();
