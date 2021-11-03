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

vector compute_direction(vector const& origin_pos, vector const& other_pos) {
    vector result {};
    for(unsigned int i = 0; i < DIMENSIONS; ++i) {
        result[i] = other_pos[i] - origin_pos[i];
    }
    double magnitude = std::sqrt(compute_magnitude_squared(result));
    std::transform(std::begin(result), std::end(result), std::begin(result), [magnitude](auto component){return component / magnitude;});
    return result;
}

vector compute_force(vector const& origin_pos, vector const& other_pos, double origin_mass, double other_mass) {
    auto direction = compute_direction(origin_pos, other_pos);
    double magnitude = GRAVITATIONAL_CONSTANT * ((origin_mass * other_mass) / (compute_magnitude_squared(direction)));
    return direction * magnitude;
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

void physics_integration(vector & modifying, vector const& factor) {
    for(unsigned int i = 0; i < DIMENSIONS; ++i) {
        modifying[i] += DT * factor[i];
    }
}

void print_vector(vector const& v) {
    std::cout << "(";
    std::for_each(std::begin(v), std::end(v), [](auto component){std::cout << component << ", ";});
    std::cout << ")\n";
}