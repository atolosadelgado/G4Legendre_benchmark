
#include "test_config.hh"

#include "CLHEP/GenericFunctions/Legendre.hh"

static void BM_CLHEP_Leg(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    Genfun::Legendre a(order);
    for (auto _ : state) {
        for (double x : inputs) {
            sum+=a(x);
        }
    }
    benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_CLHEP_Leg)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10

TEST(LegendreTest, CLHEP_vs_STL) {
    for (int n = norder_min; n <= norder_max; ++n) {
        Genfun::Legendre a(n);
        for (double x : inputs) {
            double CLHEP_result = a(x);
            double stl_result = std::legendre(n, x);
            EXPECT_NEAR(CLHEP_result , stl_result, tolerance)
                << "Mismatch at n=" << n << ", x=" << x
                << " (CLHEP: " << CLHEP_result  << ", std: " << stl_result << ")";
        }
    }
}
