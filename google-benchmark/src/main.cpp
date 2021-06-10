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

int iters = 1;
// int args = 132859;
// int args = 300000;
int args = 264000;
// int args = 200000;

int args_small = 30000;
int args_rozigriv = 20000;

// Rozigriv:

BENCHMARK(benchmark_epoll)->Args({args, 10, 15})->Iterations(1);
// BENCHMARK(benchmark_process_per_socket)->Args({args, 100})->Iterations(1);
BENCHMARK(benchmark_thread_per_socket)->Args({args, 100})->Iterations(1);




BENCHMARK(benchmark_process_per_socket)
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})

    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})

    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})

    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})

    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})

    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})

    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})

    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})

    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})

    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})

    ->Iterations(1);


BENCHMARK(benchmark_thread_per_socket)
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})
    ->Args({args, 10})

    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})
    ->Args({args, 20})

    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})
    ->Args({args, 30})

    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})
    ->Args({args, 40})

    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})
    ->Args({args, 50})

    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})
    ->Args({args, 75})

    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})
    ->Args({args, 100})

    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})
    ->Args({args, 200})

    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})
    ->Args({args, 300})

    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})
    ->Args({args, 500})

    ->Args({args, 1000})
    ->Args({args, 1000})
    ->Args({args, 1000})
    ->Args({args, 1000})
    ->Args({args, 1000})
    ->Args({args, 1000})
    ->Args({args, 1000})
    ->Args({args, 1000})
    ->Args({args, 1000})
    ->Args({args, 1000})

    ->Args({args, 2000})
    ->Args({args, 2000})
    ->Args({args, 2000})
    ->Args({args, 2000})
    ->Args({args, 2000})
    ->Args({args, 2000})
    ->Args({args, 2000})
    ->Args({args, 2000})
    ->Args({args, 2000})
    ->Args({args, 2000})
    ->Args({args, 2000})

    ->Args({args, 3000})
    ->Args({args, 3000})
    ->Args({args, 3000})
    ->Args({args, 3000})
    ->Args({args, 3000})
    ->Args({args, 3000})
    ->Args({args, 3000})
    ->Args({args, 3000})
    ->Args({args, 3000})
    ->Args({args, 3000})

    ->Args({args, 5000})
    ->Args({args, 5000})
    ->Args({args, 5000})
    ->Args({args, 5000})
    ->Args({args, 5000})
    ->Args({args, 5000})
    ->Args({args, 5000})
    ->Args({args, 5000})
    ->Args({args, 5000})
    ->Args({args, 5000})

    ->Iterations(1);


BENCHMARK(benchmark_epoll)
     ->Args({args, 10, 10})
     ->Args({args, 10, 10})
     ->Args({args, 10, 10})
     ->Args({args, 10, 10})
     ->Args({args, 10, 10})
     ->Args({args, 10, 10})
     ->Args({args, 10, 10})
     ->Args({args, 10, 10})
     ->Args({args, 10, 10})

     ->Args({args, 10, 25})
     ->Args({args, 10, 25})
     ->Args({args, 10, 25})
     ->Args({args, 10, 25})
     ->Args({args, 10, 25})
     ->Args({args, 10, 25})
     ->Args({args, 10, 25})
     ->Args({args, 10, 25})
     ->Args({args, 10, 25})

     ->Args({args, 10, 50})
     ->Args({args, 10, 50})
     ->Args({args, 10, 50})
     ->Args({args, 10, 50})
     ->Args({args, 10, 50})
     ->Args({args, 10, 50})
     ->Args({args, 10, 50})
     ->Args({args, 10, 50})
     ->Args({args, 10, 50})
     ->Args({args, 10, 50})

     ->Args({args, 10, 100})
     ->Args({args, 10, 100})
     ->Args({args, 10, 100})
     ->Args({args, 10, 100})
     ->Args({args, 10, 100})
     ->Args({args, 10, 100})
     ->Args({args, 10, 100})
     ->Args({args, 10, 100})
     ->Args({args, 10, 100})
     ->Args({args, 10, 100})

     ->Args({args, 10, 200})
     ->Args({args, 10, 200})
     ->Args({args, 10, 200})
     ->Args({args, 10, 200})
     ->Args({args, 10, 200})
     ->Args({args, 10, 200})
     ->Args({args, 10, 200})
     ->Args({args, 10, 200})
     ->Args({args, 10, 200})
     ->Args({args, 10, 200})

     ->Args({args, 10, 300})
     ->Args({args, 10, 300})
     ->Args({args, 10, 300})
     ->Args({args, 10, 300})
     ->Args({args, 10, 300})
     ->Args({args, 10, 300})
     ->Args({args, 10, 300})
     ->Args({args, 10, 300})
     ->Args({args, 10, 300})
     ->Args({args, 10, 300})


     ->Args({args, 20, 10})
     ->Args({args, 20, 10})
     ->Args({args, 20, 10})
     ->Args({args, 20, 10})
     ->Args({args, 20, 10})
     ->Args({args, 20, 10})
     ->Args({args, 20, 10})
     ->Args({args, 20, 10})
     ->Args({args, 20, 10})
     ->Args({args, 20, 10})

     ->Args({args, 20, 25})
     ->Args({args, 20, 25})
     ->Args({args, 20, 25})
     ->Args({args, 20, 25})
     ->Args({args, 20, 25})
     ->Args({args, 20, 25})
     ->Args({args, 20, 25})
     ->Args({args, 20, 25})
     ->Args({args, 20, 25})

     ->Args({args, 20, 50})
     ->Args({args, 20, 50})
     ->Args({args, 20, 50})
     ->Args({args, 20, 50})
     ->Args({args, 20, 50})
     ->Args({args, 20, 50})
     ->Args({args, 20, 50})
     ->Args({args, 20, 50})
     ->Args({args, 20, 50})
     ->Args({args, 20, 50})

     ->Args({args, 20, 100})
     ->Args({args, 20, 100})
     ->Args({args, 20, 100})
     ->Args({args, 20, 100})
     ->Args({args, 20, 100})
     ->Args({args, 20, 100})
     ->Args({args, 20, 100})
     ->Args({args, 20, 100})
     ->Args({args, 20, 100})
     ->Args({args, 20, 100})

     ->Args({args, 20, 200})
     ->Args({args, 20, 200})
     ->Args({args, 20, 200})
     ->Args({args, 20, 200})
     ->Args({args, 20, 200})
     ->Args({args, 20, 200})
     ->Args({args, 20, 200})
     ->Args({args, 20, 200})
     ->Args({args, 20, 200})
     ->Args({args, 20, 200})

     ->Args({args, 30, 10})
     ->Args({args, 30, 10})
     ->Args({args, 30, 10})
     ->Args({args, 30, 10})
     ->Args({args, 30, 10})
     ->Args({args, 30, 10})
     ->Args({args, 30, 10})
     ->Args({args, 30, 10})
     ->Args({args, 30, 10})
     ->Args({args, 30, 10})

     ->Args({args, 30, 25})

     ->Args({args, 30, 25})
     ->Args({args, 30, 25})
     ->Args({args, 30, 25})
     ->Args({args, 30, 25})
     ->Args({args, 30, 25})
     ->Args({args, 30, 25})
     ->Args({args, 30, 25})
     ->Args({args, 30, 25})
     ->Args({args, 30, 25})

     ->Args({args, 30, 50})
     ->Args({args, 30, 50})
     ->Args({args, 30, 50})
     ->Args({args, 30, 50})
     ->Args({args, 30, 50})
     ->Args({args, 30, 50})
     ->Args({args, 30, 50})
     ->Args({args, 30, 50})
     ->Args({args, 30, 50})
     ->Args({args, 30, 50})

     ->Args({args, 30, 100})
     ->Args({args, 30, 100})
     ->Args({args, 30, 100})
     ->Args({args, 30, 100})
     ->Args({args, 30, 100})
     ->Args({args, 30, 100})
     ->Args({args, 30, 100})
     ->Args({args, 30, 100})
     ->Args({args, 30, 100})
     ->Args({args, 30, 100})



     ->Args({args, 40, 10})
     ->Args({args, 40, 10})
     ->Args({args, 40, 10})
     ->Args({args, 40, 10})
     ->Args({args, 40, 10})
     ->Args({args, 40, 10})
     ->Args({args, 40, 10})
     ->Args({args, 40, 10})
     ->Args({args, 40, 10})
     ->Args({args, 40, 10})

     ->Args({args, 40, 25})
     ->Args({args, 40, 25})
     ->Args({args, 40, 25})
     ->Args({args, 40, 25})
     ->Args({args, 40, 25})
     ->Args({args, 40, 25})
     ->Args({args, 40, 25})
     ->Args({args, 40, 25})
     ->Args({args, 40, 25})
     ->Args({args, 40, 25})

     ->Args({args, 40, 50})
     ->Args({args, 40, 50})
     ->Args({args, 40, 50})
     ->Args({args, 40, 50})
     ->Args({args, 40, 50})
     ->Args({args, 40, 50})
     ->Args({args, 40, 50})
     ->Args({args, 40, 50})
     ->Args({args, 40, 50})
     ->Args({args, 40, 50})

     ->Args({args, 40, 100})
     ->Args({args, 40, 100})
     ->Args({args, 40, 100})
     ->Args({args, 40, 100})
     ->Args({args, 40, 100})
     ->Args({args, 40, 100})
     ->Args({args, 40, 100})
     ->Args({args, 40, 100})
     ->Args({args, 40, 100})
     ->Args({args, 40, 100})

     ->Args({args, 50, 10})
     ->Args({args, 50, 10})
     ->Args({args, 50, 10})
     ->Args({args, 50, 10})
     ->Args({args, 50, 10})
     ->Args({args, 50, 10})
     ->Args({args, 50, 10})
     ->Args({args, 50, 10})
     ->Args({args, 50, 10})
     ->Args({args, 50, 10})

     ->Args({args, 50, 25})
     ->Args({args, 50, 25})
     ->Args({args, 50, 25})
     ->Args({args, 50, 25})
     ->Args({args, 50, 25})
     ->Args({args, 50, 25})
     ->Args({args, 50, 25})
     ->Args({args, 50, 25})
     ->Args({args, 50, 25})
     ->Args({args, 50, 25})

     ->Args({args, 50, 50})
     ->Args({args, 50, 50})
     ->Args({args, 50, 50})
     ->Args({args, 50, 50})
     ->Args({args, 50, 50})
     ->Args({args, 50, 50})
     ->Args({args, 50, 50})
     ->Args({args, 50, 50})
     ->Args({args, 50, 50})
     ->Args({args, 50, 50})

    ->Iterations(1);



// first argument in epol is number of workers, second- max_requests

// Time in seconds, as a constraint
// BENCHMARK(benchmark_epoll)->Range(16, 4<<10)->Iterations(5);
// BENCHMARK(BM_StringCreation)->Args({10, 0})->Arg(100)->Arg(1000)->MinTime(1);

BENCHMARK_MAIN();
