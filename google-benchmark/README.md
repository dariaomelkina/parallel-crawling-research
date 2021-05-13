### Google BenchMark Installation 
This describes the installation process using cmake. As pre-requisites, you'll
need git and cmake installed.

```bash
# Check out the library.
$ git clone https://github.com/google/benchmark.git
# Benchmark requires Google Test as a dependency. Add the source tree as a subdirectory.
$ git clone https://github.com/google/googletest.git benchmark/googletest
# Go to the library root directory
$ cd benchmark
# Make a build directory to place the build output.
$ cmake -E make_directory "build"
# Generate build system files with cmake.
$ cmake -E chdir "build" cmake -DCMAKE_BUILD_TYPE=Release ../
# or, starting with CMake 3.13, use a simpler form:
# cmake -DCMAKE_BUILD_TYPE=Release -S . -B "build"
# Build the library.
$ cmake --build "build" --config Release
```
This builds the `benchmark` and `benchmark_main` libraries and tests.
On a unix system, the build directory should now look something like this:

```
/benchmark
  /build
    /src
      /libbenchmark.a
      /libbenchmark_main.a
    /test
      ...
```

Next, you can run the tests to check the build.

```bash
$ cmake -E chdir "build" ctest --build-config Release
```

#### You should also probably run the command below:
If you want to install the library globally, also run:
```
sudo cmake --build "build" --config Release --target install
```

### Usage:
After all of the above is completed, benchmark main.cpp:

```bash
cd google-benchmark
mkdir bin && cd bin
cmake .. && make
./google-benchmark
``` 