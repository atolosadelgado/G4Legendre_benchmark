#ifndef TEST_CONFIG
#define TEST_CONFIG

#include <benchmark/benchmark.h>
#include <gtest/gtest.h>

#include <cmath>       // for std::legendre
#include <vector>
#include <random>

constexpr int niterations  = 1;
constexpr int ninputs      = 1'000'000;
constexpr int norder_min   = 1 ;
constexpr int norder_max   = 35 ;
constexpr double tolerance = 1e-6;
constexpr double rel_tolerance = 1e-4;


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


#endif
