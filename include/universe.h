#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <fstream>
#include <vector>

#include "particle.h"
#include "config.h"

class Universe {
public:

    /**
     * @brief      Initialize universe.
     *
     * @param[in]  config  The simulation configuration
     */
    Universe(const Config& config);

    /**
     * @brief      Makes a simulation step.
     */
    void makeStep();

    /**
     * @brief      Saves all particle positions in file.
     *
     * @param      file    The file where to save all positions
     */
    void saveStep(std::ofstream& file);

    /**
     * @brief      Adds a particle.
     *
     * @param[in]  particle  The particle
     */
    void addParticle(const Particle& particle);

    /**
     * @brief      Sum an acceleration contribution to the actual
     * acceleration of all particles.
     *
     * @param[in]  accelerationContribution  The acceleration contribution
     */
    void applyAccelerationToParticles(const std::array<double, 3>& accelerationContribution);

    /**
     * @brief      Computes and applies gravitational forces between all particles.
     */
    void computeGravitationalForces();

    /**
     * @brief      Computes and resolve particle collisions between all particles.
     */
    void computeParticleCollisions();

    /**
     * @brief      Compute and resolve particle collisions between all boxes.
     *
     * @param      particle  The particle
     */
    void computeBoxesCollision(Particle& particle);

    /**
     * @brief      Return the vector containing all particles.
     *
     * @return     The vector containing all particles
     */
    std::vector<Particle> const& getParticles() const;

    /**
     * @brief      Toggle the gravitational forces.
     */
    void toggleGravity();

    /**
     * @brief      Return the gravitational forces state.
     *
     * @return     The gravitational forces state
     */
    bool getIsGravity();


    double m_simuationTime = 0; ///< Current time in the universe.
    bool m_isRunning = false;   ///< Universe running state.

private:
    const Config m_config;                      ///< Configuration of the universe.
    std::vector<Particle> m_particles;          ///< Vector containing all particles.
    std::vector<Box> m_boxes;                   ///< Vector containing all boxes.
    bool m_applyGravity;                        ///< Vector containing all boxes.
    std::array<double, 3> m_globalAcceleration; ///< Acceleration force apply on all universe.
    double m_speedFactor;                       ///< Speed factor apply to simulation time.
    const double m_G = 6.67430e-11;             ///< Gravitational constant

};

#endif // UNIVERSE_H
