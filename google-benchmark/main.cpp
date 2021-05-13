#include <benchmark/benchmark.h>
#include <iostream>

static void BM_StringCreation(benchmark::State& state) {
    for (auto _ : state){
        state.PauseTiming();
        // preparing data if needed here
        state.ResumeTiming();
        // fell free to call your function here and benchmark it
//        std::cout << 'dskfkdsf' << std::endl;
        for (int i = 0; i < state.range(0); ++i) {
            std::string empty_string;

        }
    }
}
// Register the function as a benchmark and passing an argument
BENCHMARK(BM_StringCreation)->Args({10, 0})->Arg(100)->Arg(1000);

BENCHMARK_MAIN();
