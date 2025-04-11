#include "test_config.hh"


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

