add_executable(foo foo.cc)
target_compile_features(foo PRIVATE cxx_range_for)
target_link_libraries(foo gflags)
target_link_libraries(foo ${Boost_LIBRARIES})
