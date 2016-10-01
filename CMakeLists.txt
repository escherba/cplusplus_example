include(ExternalProject)
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(cplusplus_example CXX)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# if (EXISTS "${PROJECT_SOURCE_DIR}/gflags/CMakeLists.txt")
#   add_subdirectory(gflags)
# else ()
#   find_package(gflags REQUIRED)
# endif ()

ExternalProject_Add (gflags
    GIT_REPOSITORY https://github.com/gflags/gflags.git
    GIT_TAG v2.1.2
    UPDATE_DISCONNECTED 1
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/ext"
    )

# Always use Boost's shared libraries.
set(Boost_USE_STATIC_LIBS OFF)

# We need this for all tests to use the dynamic version.
add_definitions(-DBOOST_TEST_DYN_LINK)

# Always use multi-threaded Boost libraries.
set(Boost_USE_MULTI_THREADED ON)

find_package(Boost 1.58.0 REQUIRED COMPONENTS system)


set(Gflags_LIBRARIES
    "./build/ext/lib/libgflags.a"
    "./build/ext/lib/libgflags_nothreads.a"
    )

enable_testing()

add_subdirectory(test)
add_subdirectory(src)
add_subdirectory(src/foo)


if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
  # Use C++11 when using GNU compilers.
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
  # We want to link in C++11 mode in Clang too, but also set a high enough
  # template depth for the template metaprogramming.
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ftemplate-depth=256 -std=c++11")
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
