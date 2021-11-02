#include <array>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "constants.hpp"
#include "vector.hpp"

/*
    TODO: Clean up everything
        Move vector-based computations to vector.hpp
        Refactor apply_force()
        See if you can debug correct orbit
*/


struct Body {    
    double mass;
    vector position;
    vector velocity;
    vector acceleration;
};

vector compute_direction(vector const& origin_pos, vector const& other_pos) {
    vector result {};
    for(unsigned int i = 0; i < DIMENSIONS; ++i) {
        result[i] = other_pos[i] - origin_pos[i];
    }
    double magnitude = std::sqrt(compute_magnitude_squared(result));
    std::transform(std::begin(result), std::end(result), std::begin(result), [magnitude](auto component){return component / magnitude;});
    return result;
}

vector compute_direction(Body const& origin, Body const& other) {
    return compute_direction(origin.position, other.position);
}

vector compute_force(vector const& origin_pos, vector const& other_pos, double origin_mass, double other_mass) {
    auto direction = compute_direction(origin_pos, other_pos);
    double magnitude = GRAVITATIONAL_CONSTANT * ((origin_mass * other_mass) / (compute_magnitude_squared(direction)));
    return direction * magnitude;
}

vector compute_force(Body const& origin, Body const& other) {
    return compute_force(origin.position, other.position, origin.mass, other.mass);
}

vector compute_acceleration(vector const& origin_pos, vector const& other_pos, double origin_mass, double other_mass) {
    vector result {};
    vector force = compute_force(origin_pos, other_pos, origin_mass, other_mass);
    std::transform(std::begin(force), std::end(force), std::begin(result), [other_mass](auto component){return component / other_mass;});
    return result;
}

void apply_force(Body &b, vector const& force) {
    std::transform(std::begin(force), std::end(force), std::begin(b.acceleration), [&b](auto coord){return coord / b.mass;});
    for(unsigned int i = 0; i < b.velocity.size(); ++i) {
        b.velocity[i] += DT * b.acceleration[i];
    }

    for(unsigned int i = 0; i < b.position.size(); ++i) {
        b.position[i] += DT * b.velocity[i];
    }
}

int main() {
    double sun_mass = 1.989e30;
    double earth_mass = 5.972e24;
    vector sun_position {0.0, 0.0};
    vector earth_position {PERIAPSIS, 0.0};
    Body sun {sun_mass, sun_position, {0.0, 0.0}, {0.0, 0.0} };
    Body earth {earth_mass, earth_position, {0.0, V_PERIAPSIS}, compute_acceleration(sun_position, earth_position, sun_mass, earth_mass) };
    double year = DT * 365;

    do {
        vector gravitational_force = compute_force(sun, earth);
        std::cout << "Force: ";
        print_vector(gravitational_force);
        apply_force(earth, gravitational_force);
        std::cout << "Earth Pos: ";
        print_vector(earth.position); 
        std::cout << "Earth Velocity: ";
        print_vector(earth.velocity);
        std::cout << "\n";
        year -= DT;
    } while(year > 0);

    return 0;
}