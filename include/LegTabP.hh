#ifndef LEGTABP_HH
#define LEGTABP_HH


namespace LegTabP{


#include <cmath>       // for std::legendre
#include <array>

// Max degree up to which coefficients are precalculated
constexpr int MAX_DEGREE = 10;

// A helper type to hold coefficients: coeffs[n][k] = coefficient for x^k in P_n(x)
using Poly = std::array<double, MAX_DEGREE + 1>;
using PolyTable = std::array<Poly, MAX_DEGREE + 1>;

// Zero out all coefficients
constexpr Poly zero_poly() {
    Poly p = {};
    for (auto& coeff : p) coeff = 0.0;
    return p;
}

// Multiply polynomial by scalar
constexpr Poly scale_poly(const Poly& p, double scalar) {
    Poly result = zero_poly();
    for (int i = 0; i <= MAX_DEGREE; ++i)
        result[i] = p[i] * scalar;
    return result;
}

// Multiply polynomial by x (shift coefficients right)
constexpr Poly multiply_by_x(const Poly& p) {
    Poly result = zero_poly();
    for (int i = MAX_DEGREE - 1; i >= 0; --i)
        result[i + 1] = p[i];
    return result;
}

// Add two polynomials
constexpr Poly add_poly(const Poly& a, const Poly& b) {
    Poly result = zero_poly();
    for (int i = 0; i <= MAX_DEGREE; ++i)
        result[i] = a[i] + b[i];
    return result;
}

// Generate the Legendre polynomial table at compile time
constexpr PolyTable generate_legendre_table() {
    PolyTable table{};

    // P_0(x) = 1
    table[0][0] = 1.0;

    // P_1(x) = x
    table[1][1] = 1.0;

    // Recurrence: (n+1)P_{n+1} = (2n+1)xP_n - nP_{n-1}
    for (int n = 1; n < MAX_DEGREE; ++n) {
        auto p1 = scale_poly(multiply_by_x(table[n]), 2.0 * n + 1.0);
        auto p2 = scale_poly(table[n - 1], -1.0 * n);
        auto sum = add_poly(p1, p2);
        table[n + 1] = scale_poly(sum, 1.0 / (n + 1));
    }

    return table;
}

// The precomputed table
constexpr auto legendre_table = generate_legendre_table();

// Evaluate P_n(x) using Horner's method
double eval(int n, double x) {
    if(MAX_DEGREE>=n)
    {
    const auto& coeffs = legendre_table[n];
    double result = 0.0;
    for (int i = MAX_DEGREE; i >= 0; --i)
        result = result * x + coeffs[i];
    return result;
    }
    else return std::legendre(n,x);
}

}

#endif
