#include <array>
#include <numeric>
#include <algorithm>
#include "constants.hpp"

using vector = std::array<double, DIMENSIONS>;

vector operator*(vector const& a, vector const& b) {
    // TODO: Implement this function
    return a;
}

double dot_product(vector const& a, vector const& b) {
    return std::inner_product(std::begin(a), std::end(a), std::begin(b), 0);
}

vector operator*(vector const& vec, double scalar) {
    vector result {};
    std::transform(std::begin(vec), std::end(vec), std::begin(result), [scalar](auto component){return component * scalar;});
    return result;
}

double compute_magnitude_squared(vector const& v) {
    return std::inner_product(std::begin(v), std::end(v), std::begin(v), 0);
}