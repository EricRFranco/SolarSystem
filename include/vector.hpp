#include <array>
#include <numeric>
#include <algorithm>
#include <cstddef>
#include "constants.hpp"

using vector = std::array<double, DIMENSIONS>;

double operator*(vector const& a, vector const& b) {
    return std::inner_product(std::begin(a), std::end(a), std::begin(b), double{});
}

vector operator*(vector const& vec, double const scalar) {
    vector result{};
    std::transform(std::begin(vec), std::end(vec), std::begin(result), [scalar](auto component){return component * scalar;});
    return result;
}

vector operator+(vector const& a, vector const& b) {
    vector result{};
    for(std::size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] + b[i];
    }
    return result;
}

vector operator-(vector const& vec) {
    return vec * double{-1};
}

vector operator-(vector const& a, vector const& b) {
    return a + (-b);
}

double compute_magnitude_squared(vector const& v) {
    return std::inner_product(std::begin(v), std::end(v), std::begin(v), double{});
}

vector normalize(vector const& vec) {
    vector result {};
    double magnitude = std::sqrt(compute_magnitude_squared(vec));
    std::transform(std::begin(vec), std::end(vec), std::begin(result), [magnitude](auto component){return component / magnitude;});
    return result;
}

vector compute_force(vector const& origin_pos, vector const& other_pos, double origin_mass, double other_mass) {
    auto direction = origin_pos - other_pos;
    double magnitude = GRAVITATIONAL_CONSTANT * ((origin_mass * other_mass) / (compute_magnitude_squared(direction)));
    return normalize(direction) * magnitude;
}

vector compute_acceleration(vector const& force, double mass) {
    vector result {};
    std::transform(std::begin(force), std::end(force), std::begin(result), [mass](auto component){return component / mass;});
    return result;
}

vector compute_acceleration(vector const& origin_pos, vector const& other_pos, double origin_mass, double other_mass) {
    auto force = compute_force(origin_pos, other_pos, origin_mass, other_mass);
    return compute_acceleration(force, other_mass);
}

vector physics_integration(vector const& derivative, vector const& factor) {
    vector result{derivative};
    for(std::size_t i = 0; i < DIMENSIONS; ++i) {
        result[i] += DT * factor[i];
    }
    return result;
}

void print_vector(vector const& v) {
    std::cout << "(";
    std::for_each(std::begin(v), std::end(v), [](auto component){std::cout << component << ", ";});
    std::cout << ")\n";
}