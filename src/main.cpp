#include <array>
#include <algorithm>

static int constexpr DIMENSIONS = 2;
static float constexpr DT = 0.01;

struct Body {
    float mass;
    std::array<float, DIMENSIONS> position;
    std::array<float, DIMENSIONS> velocity;
    std::array<float, DIMENSIONS> acceleration;
    
};

void update(Body &b, std::array<float, DIMENSIONS> const& force) {
    std::transform(std::begin(force), std::end(force), std::begin(b.acceleration), [&b](auto coord){return coord / b.mass;});
    for(int i = 0; i < b.velocity.size(); ++i) {
        b.velocity[i] = DT * b.acceleration[i];
    }

    for(int i = 0; i < b.position.size(); ++i) {
        b.position[i] = DT * b.velocity[i];
    }
}

int main() {
    return 0;
}