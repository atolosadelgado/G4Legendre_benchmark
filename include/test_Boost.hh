#include "test_config.hh"

#include <boost/math/special_functions/legendre.hpp>
static void BM_Boost(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    for (auto _ : state) {
        for (double x : inputs) {
            sum += boost::math::legendre_p(order, x);
        }
    }
    benchmark::DoNotOptimize(sum);
}
BENCHMARK(BM_Boost)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10

TEST(LegendreTest, Boost_vs_STL) {
    for (double x : inputs) {
        for (int n = norder_min; n <= norder_max; ++n) {
            double Boost_result = boost::math::legendre_p(n, x);
            double stl_result = std::legendre(n, x);

            EXPECT_NEAR(Boost_result, stl_result, tolerance)
                << "Mismatch at n=" << n << ", x=" << x
                << " (Boost: " << Boost_result << ", std: " << stl_result << ")";
        }
    }
}
