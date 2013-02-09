# duck - concept-based overloading for C++11
`duck` is a template metaprogramming library providing primitives to check
whether a type models a given concept. Basically, this is a reimplementation
of _Boost.ConceptCheck_ where concepts are metafunctions returning booleans
instead of triggering compilation failure.


## Requirements
A conformant C++11 compiler and standard library.


## Getting started
`duck` is a header only library. Just add the _include_ directory to your
compiler's search path and you are good to go. All you need to do is

    #include <duck.hpp>


## Running the tests
To run the tests, you will also need to have CMake installed.
If this is the case, you can go to the root of the project and do:

`make gen-cmake` --> Generates CMake files in the _build/_ directory.

`make unit-tests` --> Compiles the tests. All tests are compile-time only.
