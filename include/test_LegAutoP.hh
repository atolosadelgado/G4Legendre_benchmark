
#include "test_config.hh"

#include "../include/LegAutoP.hh"
static void BM_LegAutoP(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    for (auto _ : state) {
        for (double x : inputs) {
            sum += LegAutoP::eval(order,x);
        }
    }
    benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_LegAutoP)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10


// LegAutoP check for correctness
TEST(LegendreTest, LegAutoP_vs_STL) {
    for (double x : inputs) {
        for (int n = 0; n <= 5; ++n) {
            double LegAutoP_result = LegAutoP::eval(n, x);
            double stl_result = std::legendre(n, x);

            EXPECT_NEAR(LegAutoP_result, stl_result, tolerance)
                << "Mismatch at n=" << n << ", x=" << x
                << " (LegAutoP: " << LegAutoP_result << ", std: " << stl_result << ")";
        }
    }
}
