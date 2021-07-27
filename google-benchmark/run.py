import subprocess
from time import sleep

compiler_flags = ['-DCMAKE_CXX_COMPILER=clang', '-DCMAKE_CXX_COMPILER=g++']

opt_flags = ['-DCMAKE_CXX_FLAGS_DEBUG="-O0"',
    '-DCMAKE_CXX_FLAGS_DEBUG="-O1"',
    '-DCMAKE_CXX_FLAGS_DEBUG="-O2"',
    '-DCMAKE_CXX_FLAGS_DEBUG="-O3"',
    '-DCMAKE_CXX_FLAGS_DEBUG="-march=native"']


i = 0
for compiler_flag in compiler_flags:
    for opt_flag in opt_flags:
        compiler_name = "clang" if "clang" in compiler_flag else "gcc"
        print(compiler_name)
        opt_name = opt_flag.split('-')[-1].replace('"', '').replace("=native", "")
        print(opt_name)
        # with subprocess.Popen(f"""make clean && cmake {compiler_flag} {opt_flag} -S .. -B "build" && make && ./google-benchmark --benchmark_format=console --benchmark_out=../benchmarks.csv --benchmark_out_format=csv""") as process:
        subprocess.run(f"""make clean && cmake {compiler_flag} {opt_flag} -S .. -B "build" && make && ./google-benchmark --benchmark_format=console --benchmark_out=../{compiler_name}_{opt_name}.csv --benchmark_out_format=csv""", shell=True)
        sleep(0)
        i += 1
            # take the output and process it or smth??



# compiler_flags = ['-DCMAKE_CXX_COMPILER=clang++',
#     '-DCMAKE_CXX_COMPILER=g++']

# opt_flags = ['-DCMAKE_CXX_FLAGS_DEBUG="-O0"',
#     '-DCMAKE_CXX_FLAGS_DEBUG="-O1"',
#     '-DCMAKE_CXX_FLAGS_DEBUG="-O2"',
#     '-DCMAKE_CXX_FLAGS_DEBUG="-O3"',
#          '-DCMAKE_CXX_FLAGS_DEBUG="-march=native"']
