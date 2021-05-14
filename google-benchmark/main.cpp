#include <benchmark/benchmark.h>
#include <iostream>

static void BM_StringCreation(benchmark::State& state) {
    for (auto _ : state){
        state.PauseTiming();
        // preparing data if needed here
        state.ResumeTiming();

        // тут
    }
}
// Register the function as a benchmark and passing an argument, number of iterations as a constraint
 BENCHMARK(BM_StringCreation)->Iterations(1000);
// Time in seconds, as a constraint
//BENCHMARK(BM_StringCreation)->Args({10, 0})->Arg(100)->Arg(1000)->MinTime(1);

BENCHMARK_MAIN();
