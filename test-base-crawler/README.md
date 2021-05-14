## ! Important !
That implementation of crawler is currently not used in the project and was created for testing purposes. 

### Base crawler
Basic crawler implemented in C++ for further usage in the project.
Used in order for other crawlers to have a consistent architecture and, therefore,
be suitable for testing.

### Usage for demonstration:
From that directory:
```bash
mkdir build
cmake -Bbuild -DCMAKE_BUILD_TYPE=RelWithDebInfo && make -C ./build
./build/test-base-crawler
```
### Requirements:
* [tbb](https://software.intel.com/content/www/us/en/develop/documentation/tbb-tutorial/top.html)

