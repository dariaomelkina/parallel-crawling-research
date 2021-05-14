#include <benchmark/benchmark.h>
#include <iostream>

static void BM_StringCreation(benchmark::State& state) {
    for (auto _ : state){
        state.PauseTiming();
        // preparing data if needed here
        state.ResumeTiming();
        // feel free to call your function here and benchmark it
//        std::cout << 'dskfkdsf' << std::endl;
        for (int i = 0; i < state.range(0); ++i) {
            std::string empty_string;
        }
    }
}
// Register the function as a benchmark and passing an argument, number of iterations as a constraint
// BENCHMARK(BM_StringCreation)->Args({10, 0})->Arg(100)->Arg(1000)->Iterations(100);
// Time in seconds, as a constraint
BENCHMARK(BM_StringCreation)->Args({10, 0})->Arg(100)->Arg(1000)->MinTime(1);

//// function to benchmark multiple thread programs
//static void BM_MultiThreaded(benchmark::State& state) {
//    if (state.thread_index == 0) {
//        // Setup code here.
//    }
//    for (auto _ : state) {
//        // Run the test as normal.
//    }
//    if (state.thread_index == 0) {
//        // Teardown code here.
//    }
//}
//BENCHMARK(BM_MultiThreaded)->Threads(2);

BENCHMARK_MAIN();
