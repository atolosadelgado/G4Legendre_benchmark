#include "test_STL.hh"
#include "test_Boost.hh"
#include "test_LegTabP.hh"
#include "test_LegAutoP.hh"

#include "test_G4NuclNuclDiffuseElastic.hh"
#include "test_G4LegendrePolynomial.hh"
#include "test_G4LegendrePolynomial_assoc.hh"
#include "test_G4ABLA.hh"
#include "test_G4ParticleHPFastLegendre.hh"
#include "test_CLHEP.hh"

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

