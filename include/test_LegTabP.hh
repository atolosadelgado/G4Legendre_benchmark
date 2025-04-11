
#include "test_config.hh"

#include "../include/LegTabP.hh"
static void BM_LegTabP(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    for (auto _ : state) {
        for (double x : inputs) {
            sum += LegTabP::eval(order,x);
        }
    }
    benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_LegTabP)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10

TEST(LegendreTest, LegTabP_vs_STL) {
    for (double x : inputs) {
        for (int n = norder_min; n <= norder_max; ++n) {
            double LegAutoP_result = LegTabP::eval(n, x);
            double stl_result = std::legendre(n, x);

            EXPECT_NEAR(LegAutoP_result, stl_result, tolerance)
                << "Mismatch at n=" << n << ", x=" << x
                << " (LegTabP: " << LegAutoP_result << ", std: " << stl_result << ")";
        }
    }
}
