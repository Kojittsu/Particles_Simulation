#include "universe.h"
#include "renderer.hpp"
#include <stdexcept>
#include <cmath>

// Constructor
Universe::Universe(const Config& config)
    :
      m_boxOriginX(config.boxOriginX),
      m_boxOriginY(config.boxOriginY),
      m_boxLength(config.boxLength),
      m_boxHeight(config.boxHeight),
      m_circleX(config.circleX),
      m_circleY(config.circleY),
      m_circleRadius(config.circleRadius),
      m_scaleFactorPixels(config.scaleFactorPixels),
      m_particles(config.particles),
      m_coefficientRestitution(config.coefficientRestitution),
      m_deltaTime(config.deltaTime),
      m_applyGravity(config.applyGravity),
      m_globalAcceleration(config.globalAcceleration),
      m_speedFactor(config.speedFactor),
      m_dataFileName(config.dataFileName)
{
    // Add random particles to universe
    for(int i = 0; i < config.rndParticle_numbers; ++i){
        addRndParticle(config.rndParticle_maxVelocityX, config.rndParticle_maxVelocityY, config.rndParticle_minRadius, config.rndParticle_maxRadius, config.rndParticle_minMass, config.rndParticle_maxMass);
    }
    applyAccelerationToParticles(m_globalAcceleration);
}

void Universe::makeStep(){
    // Apply Newton's law of universal gravitation
    if(m_applyGravity){
        computeGravitationalForces();
    }
    
    for (Particle& particle : m_particles) {
        // Update particle
        particle.update(m_deltaTime);

        // Handle box collisions
        handleBoxCollision(particle);

        // Handle circle collisions if circle radius isn't null.
        if (m_circleRadius != 0) {
            handleCircleCollision(particle);
        }
    }
    // Handle particles collisions
    handleParticleCollisions();

    // Update runtime
    m_runTime += m_deltaTime;
}

void Universe::saveStep(std::ofstream& file, int stepNumber){
    if (!file.is_open()) {
        throw std::runtime_error("File is not open");
    }
    double currentTime = stepNumber * m_deltaTime;
    int particleNumber = 1;
    for (const Particle& particle : m_particles){
        file << currentTime << "," << particleNumber << "," << particle.getX() << "," << particle.getY() << "\n";
        ++particleNumber;
    }
}

void Universe::addParticle(const Particle& particle){
    m_particles.push_back(particle);
}

void Universe::addRndParticle(double maxVelocityX, double maxVelocityY, double minRadius, double maxRadius, double minMass, double maxMass){
    std::array<double, 2> position = {rndNumber(m_boxOriginX, m_boxOriginX + m_boxLength), rndNumber(m_boxOriginY, m_boxOriginY + m_boxHeight)};
    std::array<double, 2> velocity = {rndNumber(-maxVelocityX, maxVelocityX), rndNumber(-maxVelocityY, maxVelocityY)};
    double radius = rndNumber(minRadius, maxRadius);
    double mass = rndNumber(minMass, maxMass);

    Particle particle(position, velocity, m_globalAcceleration, radius, mass, getRainbow());
    m_particles.push_back(particle);
}

void Universe::applyAccelerationToParticles(const std::array<double, 2>& accelerationContribution){
    for (Particle& particle : m_particles){
        particle.setAcceleration(particle.getAcceleration() + accelerationContribution);
    }
}

void Universe::computeGravitationalForces(){
    for (Particle& particle : m_particles) {
        // Reset acceleration to global acceleration
        particle.setAcceleration(m_globalAcceleration);
    }
    
    for (size_t i = 0; i < m_particles.size(); ++i) {
        for (size_t j = i + 1; j < m_particles.size(); ++j) {
            Particle& p1 = m_particles[i];
            Particle& p2 = m_particles[j];

            std::array<double, 2> forceDirection = p2.getPosition() - p1.getPosition();
            double distance = getMagnitude(forceDirection);
            if (distance > 0) {
                double forceMagnitude = m_G * p1.getMass() * p2.getMass() / (distance * distance);
                std::array<double, 2> force = forceDirection * (forceMagnitude / distance);

                // Apply Newton's second law
                p1.setAcceleration(p1.getAcceleration() + force * (1 / p1.getMass()));
                p2.setAcceleration(p2.getAcceleration() - force * (1 / p2.getMass()));
            }
        }
    }
}

void Universe::handleParticleCollisions(){
    for (size_t i = 0; i < m_particles.size(); ++i) {
        for (size_t j = i + 1; j < m_particles.size(); ++j) {
            Particle& p1 = m_particles[i];
            Particle& p2 = m_particles[j];

            std::array<double, 2> distanceVector = p1.getPosition() - p2.getPosition();
            double distance = getMagnitude(distanceVector);
            double minDistance = p1.getRadius() + p2.getRadius();

            if (distance < minDistance) {
                std::array<double, 2> distanceVectorNormalized = distanceVector * (1 / distance);
                double overlap = minDistance - distance;
                p1.setPosition(p1.getPosition() + distanceVectorNormalized * (overlap / 2));
                p2.setPosition(p2.getPosition() - distanceVectorNormalized * (overlap / 2));

                std::array<double, 2> v1 = p1.getVelocity();
                std::array<double, 2> v2 = p2.getVelocity();
                std::array<double, 2> diffVelocity = v2 - v1;
                double relativeVelocity = dotProduct(diffVelocity, distanceVectorNormalized);

                double m1 = p1.getMass();
                double m2 = p2.getMass();
                double massSum = m1 + m2;
                double impulse = (2 * relativeVelocity) / massSum;

                p1.setVelocity(v1 + impulse * m2 * distanceVectorNormalized * m_coefficientRestitution);
                p2.setVelocity(v2 - impulse * m1 * distanceVectorNormalized * m_coefficientRestitution);
            }
        }
    }
}

void Universe::handleBoxCollision(Particle& particle){
    std::array<double, 2> position = particle.getPosition();
    std::array<double, 2> velocity = particle.getVelocity();
    double radius = particle.getRadius();

    // Check for collisions on all sides and adjust position and velocity
    if (position[0] < m_boxOriginX + radius) {
        particle.setX(m_boxOriginX + radius);
        particle.setVX(-velocity[0] * m_coefficientRestitution);
    } else if (position[0] > m_boxOriginX + m_boxLength - radius) {
        particle.setX(m_boxOriginX + m_boxLength - radius);
        particle.setVX(-velocity[0] * m_coefficientRestitution);
    }

    if (position[1] < m_boxOriginY + radius) {
        particle.setY(m_boxOriginY + radius);
        particle.setVY(-velocity[1] * m_coefficientRestitution);
    } else if (position[1] > m_boxOriginY + m_boxHeight - radius) {
        particle.setY(m_boxOriginY + m_boxHeight - radius);
        particle.setVY(-velocity[1] * m_coefficientRestitution);
    }
}

void Universe::handleCircleCollision(Particle& particle){
    double dx = particle.getX() - m_circleX;
    double dy = particle.getY() - m_circleY;
    double distance = std::sqrt(dx * dx + dy * dy);

    if (distance > m_circleRadius - particle.getRadius()) {
        double nx = dx / distance;
        double ny = dy / distance;

        particle.setX(m_circleX + nx * (m_circleRadius - particle.getRadius()));
        particle.setY(m_circleY + ny * (m_circleRadius - particle.getRadius()));

        double dotProd = particle.getVX() * nx + particle.getVY() * ny;

        double vnx = dotProd * nx;
        double vny = dotProd * ny;

        particle.setVX(particle.getVX() - 2 * vnx * m_coefficientRestitution);
        particle.setVY(particle.getVY() - 2 * vny * m_coefficientRestitution);
    }
}

const std::vector<Particle>& Universe::getParticles() const {
    return m_particles;
}
