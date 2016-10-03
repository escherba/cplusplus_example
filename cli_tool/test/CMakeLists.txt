
enable_testing()
add_custom_target(check ${CMAKE_CTEST_COMMAND} -V)


set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}-test)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${Gflags_INCLUDE_DIRS}
    ${Gtest_INCLUDE_DIRS}
    )

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cc)
add_executable(${PROJECT_TEST_NAME} ${CMAKE_SOURCE_DIR}/src/foo/acc.cc ${TEST_SRC_FILES})
target_compile_features(${PROJECT_TEST_NAME} PRIVATE cxx_range_for)
target_link_libraries(${PROJECT_TEST_NAME} ${Gtest_LIBRARIES})
target_link_libraries(${PROJECT_TEST_NAME} ${Gflags_LIBRARIES})
target_link_libraries(${PROJECT_TEST_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})

add_test(test ${PROJECT_TEST_NAME})
