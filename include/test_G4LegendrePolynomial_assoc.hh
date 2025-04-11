
#include "test_config.hh"

#include "G4LegendrePolynomial.hh"
// https://github.com/Geant4/geant4/blob/e58e650b32b961c8093f3dd6a2c3bc917b2552be/source/processes/hadronic/util/include/G4LegendrePolynomial.hh#L50
static void BM_G4LegendrePolynomial_assoc(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    G4LegendrePolynomial a;
    for (auto _ : state) {
        for (double x : inputs) {
            for( int m=0; m<=order; ++m){
                sum += a.EvalAssocLegendrePoly(order,m,x);
            }
        }
    }
    benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_G4LegendrePolynomial_assoc)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10

TEST(LegendreAssociatedTest, G4LegendrePolynomialAssoc_vs_STLAssoc) {
    G4LegendrePolynomial a;
    for (double x : inputs) {
        for (int l = norder_min; l <= norder_max; ++l) {
            for( int m=0; m<=l; ++m){

            double G4LegendrePolynomial_result = a.EvalAssocLegendrePoly(l,m,x);
            int condon_shortley_phase = -2*(m%2) +1;
            double stl_result = condon_shortley_phase*std::assoc_legendre(l,m, x);

            double abs_diff = std::abs( G4LegendrePolynomial_result - stl_result );
            double rel_diff = abs_diff / std::abs(stl_result);

            EXPECT_LE(rel_diff, tolerance)
                << "Relative difference too large at l,m = " << l << ", " << m
                << "\tx = " << x
                << " (G4LegendrePolynomial: " << G4LegendrePolynomial_result
                << ", STL: " << stl_result
                << ", rel_diff: " << rel_diff << ")";
            // EXPECT_NEAR(G4LegendrePolynomial_result, stl_result, 1e-3)
                // << "Mismatch at l,m = " << l << ", " << m << "\tx=" << x
                // << " (G4LegendrePolynomial: " << G4LegendrePolynomial_result << ", std: " << stl_result << ")";
            }
        }
    }
}
