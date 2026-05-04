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
     * @param[in]  universeConfig  The universe configuration
     */
    Universe(const UniverseConfig& universeConfig);

    /**
     * @brief      Destroy the universe.
     */
    ~Universe();

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
    void addParticle(Particle& particle);

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
    std::vector<Particle>& getParticles();


    /**
     * @brief      Return the vector containing all boxes.
     *
     * @return     The vector containing all boxes
     */
    std::vector<Box>& getBoxes();

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


    double simuationTime_ = 0; ///< Current time in the universe.
    bool isRunning_ = false;   ///< Universe running state.

private:
    const UniverseConfig config_;              ///< Configuration of the universe.
    std::ofstream logFile_;                    ///< Log file containing particles data.
    std::vector<Particle> particles_;          ///< Vector containing all particles.
    std::vector<Box> boxes_;                   ///< Vector containing all boxes.
    bool applyGravity_;                        ///< Vector containing all boxes.
    std::array<double, 3> globalAcceleration_; ///< Acceleration force apply on all universe.
    const double G_ = 6.67430e-11;             ///< Gravitational constant

};

#endif // UNIVERSE_H
