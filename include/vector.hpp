#include <array>
#include <numeric>
#include <algorithm>
#include "constants.hpp"

using vector = std::array<double, DIMENSIONS>;

double operator*(vector const& a, vector const& b) {
    return std::inner_product(std::begin(a), std::end(a), std::begin(b), double{});
}

vector operator*(vector const& vec, double const scalar) {
    vector result {};
    std::transform(std::begin(vec), std::end(vec), std::begin(result), [scalar](auto component){return component * scalar;});
    return result;
}

double compute_magnitude_squared(vector const& v) {
    return std::inner_product(std::begin(v), std::end(v), std::begin(v), double{});
}

void print_vector(vector const& v) {
    std::cout << "(";
    std::for_each(std::begin(v), std::end(v), [](auto component){std::cout << component << ", ";});
    std::cout << ")\n";
}