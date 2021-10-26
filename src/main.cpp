#include <array>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "constants.hpp"
#include "vector.hpp"


/*
    TODO: Create vector.hpp and vector.cpp
    TODO: Create build.sh file for easy compiling
    TODO: Finish update()
    Maybe include a constants.hpp file too for constexprs
    TODO: 2 bodies, planet and sun. Set up main loop, simulate a full year
 */

struct Body {
    
    double mass;
    double radius;
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

vector compute_force(Body const& a, Body const& b) {
    auto direction = compute_direction(a, b);
    double magnitude = GRAVITATIONAL_CONSTANT * ((a.mass * b.mass) / (compute_magnitude_squared(direction)));
    return direction * magnitude;
}

void update(Body &b, vector const& force) {
    std::transform(std::begin(force), std::end(force), std::begin(b.acceleration), [&b](auto coord){return coord / b.mass;});
    for(unsigned int i = 0; i < b.velocity.size(); ++i) {
        b.velocity[i] = DT * b.acceleration[i];
    }

    for(unsigned int i = 0; i < b.position.size(); ++i) {
        b.position[i] = DT * b.velocity[i];
    }
}

int main() {
    Body sun {198900.0, 0.0, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} };
    //Body earth {5.97219, };
    std::cout << "Compiled successfully." << std::endl;
    return 0;
}