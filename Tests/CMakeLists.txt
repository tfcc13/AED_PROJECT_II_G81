project(Tests)


include_directories(.)
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
add_subdirectory(lib/benchmark)
include_directories(lib/benchmark/include)


add_executable(Tests_run ScriptTests.cpp AirportManagerTests.cpp
        mainTest.cpp)

target_link_libraries(Tests_run gtest gtest_main benchmark benchmark_main ${CMAKE_PROJECT_NAME}_lib)

