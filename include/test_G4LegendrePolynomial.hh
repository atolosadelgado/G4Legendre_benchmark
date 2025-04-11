
#include "test_config.hh"

#include "G4LegendrePolynomial.hh"
// https://github.com/Geant4/geant4/blob/e58e650b32b961c8093f3dd6a2c3bc917b2552be/source/processes/hadronic/util/include/G4LegendrePolynomial.hh#L50
static void BM_G4LegendrePolynomial(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    G4LegendrePolynomial a;
    for (auto _ : state) {
        for (double x : inputs) {
            sum += a.EvalLegendrePoly(order,x);
        }
    }
    benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_G4LegendrePolynomial)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10

TEST(LegendreTest, G4LegendrePolynomial_vs_STL) {
    G4LegendrePolynomial a;
    for (double x : inputs) {
        for (int n = norder_min; n <= norder_max; ++n) {
            double G4LegendrePolynomial_result = a.EvalLegendrePoly(n,x);
            double stl_result = std::legendre(n, x);

            EXPECT_NEAR(G4LegendrePolynomial_result, stl_result, tolerance)
                << "Mismatch at n=" << n << ", x=" << x
                << " (G4LegendrePolynomial: " << G4LegendrePolynomial_result << ", std: " << stl_result << ")";
        }
    }
}
