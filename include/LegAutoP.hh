#ifndef LEGAUTOP_HH
#define LEGAUTOP_HH

#include <cmath>       // for std::legendre

namespace LegAutoP{

// Recursive constexpr Legendre polynomial
template <int N>
constexpr double LegAutoP(double x) {
    return ((2 * N - 1) * x * LegAutoP<N - 1>(x) - (N - 1) * LegAutoP<N - 2>(x)) / N;
}

// Base cases
template <>
constexpr double LegAutoP<0>(double x) {
    return 1.0;
}

template <>
constexpr double LegAutoP<1>(double x) {
    return x;
}

#include <cmath>  // Required for M_PI

// Runtime wrapper (optional)
double eval(int n, double x) {
    switch (n) {
        case 0: return LegAutoP<0>(x);
        case 1: return LegAutoP<1>(x);
        case 2: return LegAutoP<2>(x);
        case 3: return LegAutoP<3>(x);
        case 4: return LegAutoP<4>(x);
        case 5: return LegAutoP<5>(x);
        case 6: return LegAutoP<6>(x);
        case 7: return LegAutoP<7>(x);
        case 8: return LegAutoP<8>(x);
        case 9: return LegAutoP<9>(x);
        case 10: return LegAutoP<10>(x);
        // asymptotic approximation
        // default: return std::sqrt( 2./(n*M_PI*std::sin(std::acos(x)+1.e-6)) )*std::sin( (n+0.5)*std::acos(x)+0.25*M_PI );
        default: return std::legendre(n, x);  // or fall back to runtime computation
    }
}

} // end namespace autoleg

#endif
