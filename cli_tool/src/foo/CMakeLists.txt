include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${Gflags_INCLUDE_DIRS}
    )
add_executable(foo acc.cc foo.cc)
target_compile_features(foo PRIVATE cxx_range_for)
target_link_libraries(foo ${Gflags_LIBRARIES})
target_link_libraries(foo ${Boost_LIBRARIES})
target_link_libraries(foo ${CMAKE_THREAD_LIBS_INIT})
