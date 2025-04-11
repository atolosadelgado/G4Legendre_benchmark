
#include "test_config.hh"

#include "G4ParticleHPFastLegendre.hh"
// https://github.com/Geant4/geant4/blob/df176550b3e44cdd70406ff2b581896426b5bcbe/source/processes/hadronic/models/particle_hp/src/G4ParticleHPFastLegendre.cc#L7383
static void BM_G4PHP_Leg(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    G4ParticleHPFastLegendre a;
    for (auto _ : state) {
        for (double x : inputs) {
            sum+=a.Evaluate(order,x);
        }
    }
    benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_G4PHP_Leg)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10

TEST(LegendreTest, G4ParticleHPFastLegendre_vs_STL) {
    G4ParticleHPFastLegendre a;

    for (int n = norder_min; n <= norder_max; ++n) {
        double max_diff = 0;
        for (double x : inputs) {
            double G4ParticleHPFastLegendre_result = a.Evaluate(n,x);
            double stl_result = std::legendre(n, x);

            double abs_diff = std::abs( G4ParticleHPFastLegendre_result - stl_result );
            max_diff = std::max( abs_diff , max_diff );
            // double rel_diff = abs_diff / std::abs(stl_result);
            // EXPECT_LE(rel_diff, tolerance)
            //     << "Relative difference too large at n = " << n
            //     << "\tx = " << x
            //     << " (G4ParticleHPFastLegendre: " << G4ParticleHPFastLegendre_result
            //     << ", STL: " << stl_result
            //     << ", rel_diff: " << rel_diff << ")";

            // EXPECT_NEAR(G4ParticleHPFastLegendre_result, stl_result, tolerance)
            //     << "Mismatch at n=" << n << ", x=" << x
            //     << " (G4ParticleHPFastLegendre: " << G4ParticleHPFastLegendre_result << ", std: " << stl_result << ")";
        }
        EXPECT_LE(max_diff, tolerance)
            << "Max difference too large at n = " << n;

    }
}
