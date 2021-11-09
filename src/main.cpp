#include <array>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstddef>
#include <vector>
#include "constants.hpp"
#include "vector.hpp"

/*
    TODO: Clean up everything
        See if you can debug correct orbit
        Rename vector
        Create body header
*/

struct Body {    
    double mass;
    vector position;
    vector velocity;
    vector acceleration;
};

vector compute_force(Body const& origin, Body const& other) {
    return compute_force(origin.position, other.position, origin.mass, other.mass);
}

void compute_all_forces(std::vector<Body> const& bodies) {

}

void integrate(Body & b) {
    /*
    * Compute acceleration of all bodies
    * Update velocity and position based on acceleration
    */
   //std::cout << "Velocity Before: ";
   //print_vector(b.velocity);
    //std::cout << "Acceleration: ";
    //print_vector(b.acceleration);
   b.velocity = physics_integration(b.velocity, b.acceleration);
//    std::cout << "Velocity After: ";
//    print_vector(b.velocity); 
   b.position = physics_integration(b.position, b.velocity);
}

int main() {
    double sun_mass = 1.989e30;
    double earth_mass = 5.972e24;
    vector sun_position {0.0, 0.0};
    vector earth_position {PERIAPSIS, 0.0};
    Body sun {sun_mass, sun_position, {0.0, 0.0}, {0.0, 0.0} };
    Body earth {earth_mass, earth_position, {0.0, V_PERIAPSIS}, compute_acceleration(sun_position, earth_position, sun_mass, earth_mass) };
    //double year = DT * 365;
    std::cout << "Position: " ;
    print_vector(earth.position);
    std::cout << "Velocity: ";
    print_vector(earth.velocity);

    for(std::size_t i = 0; i < 365; ++i) {
        vector gravitational_force = compute_force(sun, earth);
        integrate(earth);
        std::cout << "Force: ";
        print_vector(gravitational_force);
        std::cout << "Earth Pos: ";
        print_vector(earth.position); 
        std::cout << "Earth Velocity: ";
        print_vector(earth.velocity);
        std::cout << "\n";
    } 

    return 0;
}