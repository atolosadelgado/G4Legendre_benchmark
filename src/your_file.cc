#include <benchmark/benchmark.h>
#include <cmath>       // for std::legendre
#include <vector>

constexpr int niterations  = 1;
constexpr int ninputs      = 1'000'000;
constexpr int norder_min   = 1 ;
constexpr int norder_max   = 33 ;
constexpr double tolerance = 1e-7;


#include <random>
#include <vector>

static std::vector<double> GenerateRandomInputs(size_t N) {
    std::mt19937 rng(42); // fixed seed for reproducibility
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    std::vector<double> values(N);
    for (auto& v : values) {
        v = dist(rng);
    }
    return values;
}

static const std::vector<double> inputs = GenerateRandomInputs(ninputs);



//___________________________________________________________________________________________________
static void BM_STL(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    for (auto _ : state) {
        for (double x : inputs) {
            sum += std::legendre(order, x);
        }
    }
    benchmark::DoNotOptimize(sum);
}
BENCHMARK(BM_STL)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10

//___________________________________________________________________________________________________
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


//___________________________________________________________________________________________________
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

//___________________________________________________________________________________________________
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

//___________________________________________________________________________________________________
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


//___________________________________________________________________________________________________
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

//___________________________________________________________________________________________________
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

//___________________________________________________________________________________________________
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


//___________________________________________________________________________________________________
#include "G4Abla.hh"
// https://github.com/Geant4/geant4/blob/df176550b3e44cdd70406ff2b581896426b5bcbe/source/processes/hadronic/models/abla/src/G4Abla.cc#L6254
static void BM_G4Abla_Leg(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    G4Abla a(nullptr);
    for (auto _ : state) {
        for (double x : inputs) {
            double pl[order];
            a.lpoly(x,order,pl);
            sum+=pl[order-1];
            for(int n=0; n<order-1; ++n) sum+=pl[n];
        }
    }
    benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_G4Abla_Leg)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10

//___________________________________________________________________________________________________
static void BM_STL_forABLA(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    for (auto _ : state) {
        for (double x : inputs) {
            double pl[order];
            for(int n=0; n<order; ++n) pl[n]=std::legendre(n,x);
            sum+=pl[order-1];
            for(int n=0; n<order-1; ++n) sum+=pl[n];
        }
    }
    benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_STL_forABLA)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10

//___________________________________________________________________________________________________
static void BM_LegAutoP_forABLA(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    for (auto _ : state) {
        for (double x : inputs) {
            double pl[order];
            for(int n=0; n<order; ++n) pl[n]=LegAutoP::eval(n,x);
            sum+=pl[order-1];
            for(int n=0; n<order-1; ++n) sum+=pl[n];
        }
    }
    benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_LegAutoP_forABLA)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10

//___________________________________________________________________________________________________
static void BM_STL_assoc(benchmark::State& state) {
    int order = state.range(0);
    double sum = 0.0;
    for (auto _ : state) {
        for (double x : inputs) {
            for( int m=0; m<=order; ++m){
                sum += std::assoc_legendre(order,m,x);
            }
        }
    }
    benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_STL_assoc)->Iterations(niterations)->DenseRange(norder_min, norder_max); // Includes 10

//___________________________________________________________________________________________________
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

//___________________________________________________________________________________________________
#include <gtest/gtest.h>
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

//___________________________________________________________________________________________________
// Boost check for correctness
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


//___________________________________________________________________________________________________
// Boost check for correctness
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

// //___________________________________________________________________________________________________
// // G4NuclNuclDiffuseElastic check for correctness
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
//___________________________________________________________________________________________________
// G4LegendrePolynomial check for correctness
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

//___________________________________________________________________________________________________
// G4LegendrePolynomial associated check for correctness
TEST(LegendreAssociatedTest, G4LegendrePolynomial_vs_STL) {
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
                << ", std: " << stl_result
                << ", rel_diff: " << rel_diff << ")";
            // EXPECT_NEAR(G4LegendrePolynomial_result, stl_result, 1e-3)
                // << "Mismatch at l,m = " << l << ", " << m << "\tx=" << x
                // << " (G4LegendrePolynomial: " << G4LegendrePolynomial_result << ", std: " << stl_result << ")";
            }
        }
    }
}


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




// BENCHMARK_MAIN();



// preliminary results see no impact between hardcoding the functions or specializing a template argument
// Simple hand-coded Legendre polynomials for low orders
// double LegendreP0(double x) { return 1.0; }
// double LegendreP1(double x) { return x; }
// double LegendreP2(double x) { return 0.5 * (3 * x * x - 1); }
// double LegendreP3(double x) { return 0.5 * x * (5 * x*x - 3) ; }
// double LegendreP4(double x) { return 0.125 * (35 * x*x*x*x - 30 * x * x + 3); }
//
//
// // Templated function for Legendre polynomials
// template <int N>
// double LegendreP(double x);
//
// // Specialization for P0(x) = 1
// template <>
// double LegendreP<0>(double x) {
//     return 1.0;
// }
//
// // Specialization for P1(x) = x
// template <>
// double LegendreP<1>(double x) {
//     return x;
// }
//
// // Specialization for P2(x) = 0.5 * (3 * x^2 - 1)
// template <>
// double LegendreP<2>(double x) {
//     return 0.5 * (3 * x * x - 1);
// }
//
// // Specialization for P3(x) = 0.5 * x * (5 * x^2 - 3)
// template <>
// double LegendreP<3>(double x) {
//     return 0.5 * x * (5 * x * x - 3);
// }
