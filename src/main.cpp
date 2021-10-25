#include <array>
#include <algorithm>
#include <numeric>

static int constexpr DIMENSIONS = 2;
static float constexpr DT = 0.01;
static float constexpr GRAVITATIONAL_CONSTANT = 0.0;

/*
    TODO: Create vector.hpp and vector.cpp
    TODO: Create build.sh file for easy compiling
    TODO: Finish update()
    Maybe include a constants.hpp file too for constexprs
    TODO: 2 bodies, planet and sun. Set up main loop, simulate a full year
 */

struct Body {
    using vector = std::array<double, DIMENSIONS>;
    double mass;
    double radius;
    vector position;
    vector velocity;
    vector acceleration;
};

Body::vector compute_direction(Body const& origin, Body const& other) {
    Body::vector result {};
    for(unsigned int i = 0; i < DIMENSIONS; ++i) {
        result[i] = other.position[i] - origin.position[i];
    }
    auto magnitude = compute_magnitude(result);
    std::transform(std::begin(result), std::end(result), std::begin(result), [magnitude](auto component){return component / magnitude;});
    return result;
}

double compute_magnitude(Body::vector const& v) {
    return std::inner_product(std::begin(v), std::end(v), std::begin(v), 0);
}

Body::vector operator*(Body::vector const& a, Body::vector const& b) {
    // TODO: Implement this function
}

Body::vector operator*(Body::vector const& vec, double scalar) {
    Body::vector result {};
    std::transform(std::begin(vec), std::end(vec), std::begin(result), [scalar](auto component){return component * scalar;});
    return result;
}

Body::vector compute_force(Body const& a, Body const& b) {
    auto direction = compute_direction(a, b);
    double magnitude = GRAVITATIONAL_CONSTANT * ((a.mass * b.mass) / (compute_magnitude(direction)));
    return direction * magnitude;
}

void update(Body &b, Body::vector const& force) {
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

    return 0;
}