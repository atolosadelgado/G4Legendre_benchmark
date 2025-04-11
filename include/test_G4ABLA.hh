
#include "test_config.hh"

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

#include "LegAutoP.hh"
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


TEST(LegendreTest, G4ABLA_vs_STL) {
    G4Abla a(nullptr);
    for (double x : inputs) {
        double pl[norder_max+1];
        a.lpoly(x,norder_max,pl);
        for (int n = norder_min; n < norder_max; ++n) {
            double G4ABLA_result = pl[n];
            double stl_result = std::legendre(n, x);

            EXPECT_NEAR(G4ABLA_result, stl_result, tolerance)
                << "Mismatch at n=" << n << ", x=" << x
                << " (G4ABLA: " << G4ABLA_result << ", std: " << stl_result << ")";
        }
    }
}
