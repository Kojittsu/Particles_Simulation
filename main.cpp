#include "particle.h"
#include "universe.h"

int main() {
    // Parameters
    const double gravite = -9.81;  // Gravity Acceleration (m/s^2)
    const double deltaTime = 0.01; // Time step of simulation (s)

    // Particles initialization
    std::vector<Particle> particles;

    std::array<double, 2> position {0.0, 10.0};
    std::array<double, 2> velocity {0.0, 0.0};
    std::array<double, 2> acceleration {0.0, gravite};


    Particle particle_1(position, velocity, acceleration);

    particles.emplace_back(particle_1); // Particle at 10m height with zero initial velocity

    // Create and run universe
    Universe universe(particles, deltaTime);
    universe.run(1000, "simulation_output.csv");

    return 0;
}
