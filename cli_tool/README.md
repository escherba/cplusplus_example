About
=====

The CLI tool is a simple reference project designed to be run from a command line.
It demonstrates the use of CMake as build tool, Boost as external dependency, 
Gflags and GoogleTeset as external dependencies that are optionally downloaded and compiled during the build process,
and GoogleTest as the main testing framework.

Building
--------

This project uses typical cmake out-of-source build pattern:

    mkdir build
    cd build
    cmake ..
    make

After building, you can run the tests either by running the test executable or, in the build directory, by issuing:

    make check
    
    
Testing
-------

In the build directory, run ``make check``. The output should look something like the following:

test 1
    Start 1: test

    1: Test command: test/cplusplus_example-test
    1: Test timeout computed to be: 9.99988e+06
    1: Running main() from gtest_main.cc
    1: [==========] Running 4 tests from 2 test cases.
    1: [----------] Global test environment set-up.
    1: [----------] 1 test from foo_test
    1: [ RUN      ] foo_test.mean_variance
    1: [       OK ] foo_test.mean_variance (0 ms)
    1: [----------] 1 test from foo_test (0 ms total)
    1: 
    1: [----------] 3 tests from cpp_sorter_test
    1: [ RUN      ] cpp_sorter_test.null_term_str_sort
    1: [       OK ] cpp_sorter_test.null_term_str_sort (0 ms)
    1: [ RUN      ] cpp_sorter_test.char_arr_sort
    1: [       OK ] cpp_sorter_test.char_arr_sort (0 ms)
    1: [ RUN      ] cpp_sorter_test.int_arr_sort
    1: [       OK ] cpp_sorter_test.int_arr_sort (0 ms)
    1: [----------] 3 tests from cpp_sorter_test (0 ms total)
    1: 
    1: [----------] Global test environment tear-down
    1: [==========] 4 tests from 2 test cases ran. (0 ms total)
    1: [  PASSED  ] 4 tests.
    1/1 Test #1: test .............................   Passed    0.00 sec
