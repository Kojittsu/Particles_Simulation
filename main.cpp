#include "particle.h"
#include "universe.h"

int main() {
    // Parameters
    const double deltaTime = 0.01; // Time step of simulation (s)

    // Particles initialization
    std::vector<Particle> particles;

    std::array<double, 2> position {0.0, 10.0};
    std::array<double, 2> velocity {1.0, 0.0};
    std::array<double, 2> acceleration {0.0, 0};
    Particle particle_1(position, velocity, acceleration);

    particles.emplace_back(particle_1);

    // Create and run universe
    Universe universe(particles, deltaTime);
    universe.run(1000, "");
    // universe.run(1000, "simulation_output.csv");

    return 0;
}
