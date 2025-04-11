#include "test_STL.hh"
#include "test_LegTabP.hh"


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::benchmark::Initialize(&argc, argv);

    // Run all tests first
    int test_result = RUN_ALL_TESTS();

    // If tests pass, run the benchmarks
    // if (test_result == 0) {
        ::benchmark::RunSpecifiedBenchmarks();
    // }

    return test_result;
}


