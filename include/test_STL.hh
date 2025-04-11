#include "test_config.hh"

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
