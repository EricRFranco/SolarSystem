#include <array>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "constants.hpp"
#include "vector.hpp"


struct Body {    
    double mass;
    vector position;
    vector velocity;
    vector acceleration;
};

vector compute_direction(Body const& origin, Body const& other) {
    vector result {};
    for(unsigned int i = 0; i < DIMENSIONS; ++i) {
        result[i] = other.position[i] - origin.position[i];
    }
    double magnitude = sqrt(compute_magnitude_squared(result));
    std::transform(std::begin(result), std::end(result), std::begin(result), [magnitude](auto component){return component / magnitude;});
    return result;
}

vector compute_force(Body const& origin, Body const& other) {
    auto direction = compute_direction(origin, other);
    double magnitude = GRAVITATIONAL_CONSTANT * ((origin.mass * other.mass) / (compute_magnitude_squared(direction)));
    return direction * magnitude;
}

void apply_force(Body &b, vector const& force) {
    std::transform(std::begin(force), std::end(force), std::begin(b.acceleration), [&b](auto coord){return coord / b.mass;});
    for(unsigned int i = 0; i < b.velocity.size(); ++i) {
        b.velocity[i] = DT * b.acceleration[i];
    }

    for(unsigned int i = 0; i < b.position.size(); ++i) {
        b.position[i] = DT * b.velocity[i];
    }
}

int main() {
    Body sun {1.989e30, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} };
    Body earth {5.972e24, {1.47e8, 0.0}, {0.0, 0.0}, {0.0, 0.0} };
    double year = DT * 365;

    do {
        vector gravitational_force = compute_force(sun, earth);
        apply_force(earth, gravitational_force);
        std::cout << "Earth moved to (";
        for(unsigned int i = 0; i < DIMENSIONS; ++i) {
            std::cout << earth.position[i];
            if(i < DIMENSIONS - 1)
                std::cout << ", ";
            else
                std::cout << ")";
        } 
        std::cout << std::endl;
        year -= DT;
    } while(year > 0);

    return 0;
}