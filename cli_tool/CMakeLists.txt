include(ExternalProject)
set(PROJECT_NAME_STR cplusplus_example)
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

project(${PROJECT_NAME_STR} CXX)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# if (EXISTS "${PROJECT_SOURCE_DIR}/gflags/CMakeLists.txt")
#   add_subdirectory(gflags)
# else ()
#   find_package(gflags REQUIRED)
# endif ()

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)

# sudo apt install libgflags-dev
find_package(Gflags QUIET)
if (Gflags_FOUND)
    # Local gflags setup has been found ('gflags' variable is set)
    message("using local installation of gflags")
    set(Gflags_LIBRARIES gflags)
else()
    # for some reason, on Ubuntu, cmake doesn't find local gfalgs
    # (but does find it on Mac OS X)
    message("did not find gflags: will download and build from source")
    ExternalProject_Add (Gflags
        GIT_REPOSITORY https://github.com/gflags/gflags.git
        GIT_TAG v2.1.2
        UPDATE_DISCONNECTED 1
        CMAKE_ARGS
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/ext
        )
    ExternalProject_Get_Property(Gflags source_dir)
    set(Gflags_INCLUDE_DIRS "${source_dir}/include")
    set(Gflags_LIBRARIES
        "${CMAKE_BINARY_DIR}/ext/lib/libgflags.a"
        )
endif()

# sudo apt install libgtest-dev
find_package(Gtest QUIET)
if (Gtest_FOUND)
    # Local gtest setup has been found ('gtest' variable is set)
    message("using local installation of gtest")
    set(Gtest_LIBRARIES gtest gtest_main)
else()
    # for some reason, on Ubuntu, cmake doesn't find local gfalgs
    # (but does find it on Mac OS X)
    message("did not find gtest: will download and build from source")
    ExternalProject_Add (Gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.7.0
        UPDATE_DISCONNECTED 1
        INSTALL_COMMAND cmake -E echo "Skipping install step"
        CMAKE_ARGS
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/ext
        )
    # for some reason, "install" target is not createed by CMake,
    # so we disable "make install" step by setting INSTALL_COMMAND
    # to an empty string and link directly to the library in the build directory
    ExternalProject_Get_Property(Gtest binary_dir)
    ExternalProject_Get_Property(Gtest source_dir)
    add_library(gtest      UNKNOWN IMPORTED)
    add_library(gtest_main UNKNOWN IMPORTED)
    set(Gtest_INCLUDE_DIRS "${source_dir}/include")
    set_target_properties(gtest PROPERTIES
        IMPORTED_LOCATION ${binary_dir}/libgtest.a
    )
    set_target_properties(gtest_main PROPERTIES
        IMPORTED_LOCATION ${binary_dir}/libgtest_main.a
    )
    set(Gtest_LIBRARIES gtest gtest_main)
endif()


# add a target to generate API documentation with Doxygen
# after https://tty1.net/blog/2014/cmake-doxygen_en.html
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})
if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()

# Always use Boost's shared libraries.
set(Boost_USE_STATIC_LIBS OFF)

# We need this for all tests to use the dynamic version.
add_definitions(-DBOOST_TEST_DYN_LINK)

# Always use multi-threaded Boost libraries.
set(Boost_USE_MULTI_THREADED ON)

find_package(Boost 1.58.0 REQUIRED COMPONENTS system filesystem)



add_subdirectory(test)
add_subdirectory(src)
add_subdirectory(src/foo)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread")


if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
  # Use C++11 when using GNU compilers.
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
  # We want to link in C++11 mode in Clang too, but also set a high enough
  # template depth for the template metaprogramming.
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-depth=256")
  if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # Use libc++ only in OS X.
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc++")
  endif()
endif()

if (Boost_FOUND)
    if (MSVC)
      add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    endif(MSVC)
    if (WIN32)
      add_definitions(-D_WIN32_WINNT=0x0501)
    endif(WIN32)
    include_directories(${Boost_INCLUDE_DIRS})
endif(Boost_FOUND)
