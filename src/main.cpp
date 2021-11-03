#include <array>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "constants.hpp"
#include "vector.hpp"

/*
    TODO: Clean up everything
        See if you can debug correct orbit
*/

struct Body {    
    double mass;
    vector position;
    vector velocity;
    vector acceleration;
};

vector compute_direction(Body const& origin, Body const& other) {
    return compute_direction(origin.position, other.position);
}

vector compute_force(Body const& origin, Body const& other) {
    return compute_force(origin.position, other.position, origin.mass, other.mass);
}

void apply_force(vector const& force, double mass, vector & accel, vector & velocity, vector & position) {
    accel = compute_acceleration(force, mass);
    physics_integration(velocity, accel);
    physics_integration(position, velocity);
}

void apply_force(vector const& force, Body &b) {
    apply_force(force, b.mass, b.acceleration, b.velocity, b.position);
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
        apply_force(gravitational_force, earth);
        std::cout << "Earth Pos: ";
        print_vector(earth.position); 
        std::cout << "Earth Velocity: ";
        print_vector(earth.velocity);
        std::cout << "\n";
        year -= DT;
    } while(year > 0);

    return 0;
}