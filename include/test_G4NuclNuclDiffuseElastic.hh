
#include "test_config.hh"

#include "G4NuclNuclDiffuseElastic.hh"
// https://github.com/Geant4/geant4/blame/e58e650b32b961c8093f3dd6a2c3bc917b2552be/source/processes/hadronic/models/coherent_elastic/src/G4NuclNuclDiffuseElastic.cc#L1441
static void BM_G4NuclNuclDiffuseElastic_cos(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    G4NuclNuclDiffuseElastic a;
    for (auto _ : state) {
        for (double i : inputs) {
            double x = std::acos( M_PI_2*i);
            sum += a.GetLegendrePol(order,x);
        }
    }
    benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_G4NuclNuclDiffuseElastic_cos)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10

static void BM_STL_cos(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    for (auto _ : state) {
        for (double i : inputs) {
            double x = std::acos( M_PI_2*i);
            sum += std::legendre(order,x);
        }
    }
    benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_STL_cos)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10

#include "../include/LegTabP.hh"
static void BM_LegTabP_cos(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    for (auto _ : state) {
        for (double i : inputs) {
            double x = std::acos( M_PI_2*i);
            sum += LegTabP::eval(order,x);
        }
    }
    benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_LegTabP_cos)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10


// differences when using the model because of asymtotic approach is used for n>6
TEST(LegendreTest, G4NuclNuclDiffuseElastic_cos_vs_STL) {
    G4NuclNuclDiffuseElastic a;

    for (int n = norder_min; n <= norder_max; ++n) {
        double max_difference = 0;
        for (double x : inputs) {
            double G4NuclNuclDiffuseElastic_result = a.GetLegendrePol(n,x);
            double stl_result = std::legendre(n, std::cos(x));
            max_difference = std::max( max_difference, fabs(stl_result - G4NuclNuclDiffuseElastic_result) );

        }
        EXPECT_NEAR(max_difference, 0.0, tolerance)
            << "Mismatch at n=" << n << ", max difference =" << max_difference ;
    }
}
