
### Usage
---
#### CMakeLists.txt
To compile an FSCIO smart contract with CMake you'll need a CMake file. The template `CMakeLists.txt` in the examples folder is a good boilerplate.

For example:

In `CMakeLists.txt`:
```
cmake_minimum_required(VERSION 3.5)
project(test_example VERSION 1.0.0)

find_package(fscio.cdt)

add_contract( test test test.cpp )
```


In `test.cpp`:

```
#include <fsciolib/fscio.hpp>
using namespace fscio;

CONTRACT test : public fscio::contract {
public:
   using contract::contract;

   ACTION testact( name test ) {
   }
};

FSCIO_DISPATCH( test, (testact) )
```

To manually compile the source code, use [`fscio-cpp/fscio-cc`](/tools/fscio-cpp.html) and [`fscio-ld`](/tools/fscio-ld.html) as if it were __clang__ and __lld__. All the includes and options specific to FSCIO and CDT are baked in.
