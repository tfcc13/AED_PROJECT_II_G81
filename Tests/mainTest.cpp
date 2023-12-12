//
// Created by tiago on 12-12-2023.
//

#include "gtest/gtest.h"
#include "benchmark/benchmark.h"

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    benchmark::Initialize(&argc, argv);
    int res = RUN_ALL_TESTS();
    benchmark::RunSpecifiedBenchmarks();
    return res;
}