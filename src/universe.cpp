#include "universe.h"

// Constructor
Universe::Universe(const Config& config)
    :
        m_config(config),
        m_particles(config.particles),
        m_boxes(config.boxes),
        m_applyGravity(config.applyGravity),
        m_globalAcceleration(config.globalAcceleration)
{
    applyAccelerationToParticles(m_globalAcceleration);
}

void Universe::makeStep(){
    // Apply Newton's law of universal gravitation
    if(m_applyGravity) {
        computeGravitationalForces();
    }
    
    for (Particle& particle : m_particles) {
        // Update particle
        particle.update(m_config.deltaTime);
        // Handle boxes collisions
        computeBoxesCollision(particle);
    }

    computeParticleCollisions();

    m_simuationTime += m_config.deltaTime;
}

void Universe::saveStep(std::ofstream& file){
    if (!file.is_open()) {
        throw std::runtime_error("File is not open");
    }
    int particleNumber = 1;
    for (const Particle& particle : m_particles){
        file << m_simuationTime << "," << particleNumber << "," << particle.getX() << "," << particle.getY() << "," << particle.getZ() << "\n";
        ++particleNumber;
    }
}

void Universe::addParticle(const Particle& particle){
    m_particles.push_back(particle);
}


void Universe::applyAccelerationToParticles(const std::array<double, 3>& accelerationContribution){
    for (Particle& particle : m_particles){
        particle.setAcceleration(particle.getAcceleration() + accelerationContribution);
    }
}

void Universe::computeGravitationalForces() {
    for (Particle& particle : m_particles) {
        // Reset acceleration to global acceleration
        particle.setAcceleration(m_globalAcceleration);
    }
    
    for (size_t i = 0; i < m_particles.size(); ++i) {
        for (size_t j = i + 1; j < m_particles.size(); ++j) {
            Particle& p1 = m_particles[i];
            Particle& p2 = m_particles[j];

            std::array<double, 3> forceDirection = p2.getPosition() - p1.getPosition();
            double distance = getMagnitude(forceDirection);
            if (distance > 0) {
                double forceMagnitude = m_G * p1.getMass() * p2.getMass() / (distance * distance);
                std::array<double, 3> force = forceDirection * (forceMagnitude / distance);

                // Apply Newton's second law
                p1.setAcceleration(p1.getAcceleration() + force * (1 / p1.getMass()));
                p2.setAcceleration(p2.getAcceleration() - force * (1 / p2.getMass()));
            }
        }
    }
}

void Universe::computeParticleCollisions() {
    for (size_t i = 0; i < m_particles.size(); ++i) {
        for (size_t j = i + 1; j < m_particles.size(); ++j) {
            Particle& p1 = m_particles[i];
            Particle& p2 = m_particles[j];

            std::array<double, 3> distanceVector = p1.getPosition() - p2.getPosition();
            double distance = getMagnitude(distanceVector);
            double minDistance = p1.getRadius() + p2.getRadius();

            // Collision detected
            if (distance < minDistance) {
                std::array<double, 3> distanceVectorNormalized = distanceVector * (1 / distance);
                double overlap = minDistance - distance;
                p1.setPosition(p1.getPosition() + distanceVectorNormalized * (overlap / 2));
                p2.setPosition(p2.getPosition() - distanceVectorNormalized * (overlap / 2));

                std::array<double, 3> v1 = p1.getVelocity();
                std::array<double, 3> v2 = p2.getVelocity();
                std::array<double, 3> diffVelocity = v2 - v1;
                double relativeVelocity = dotProduct(diffVelocity, distanceVectorNormalized);

                double m1 = p1.getMass();
                double m2 = p2.getMass();
                double massSum = m1 + m2;
                double impulse = (2 * relativeVelocity) / massSum;

                p1.setVelocity(v1 + impulse * m2 * distanceVectorNormalized * m_config.coefficientRestitution);
                p2.setVelocity(v2 - impulse * m1 * distanceVectorNormalized * m_config.coefficientRestitution);
            }
        }
    }
}

void Universe::computeBoxesCollision(Particle& particle) {
    std::array<double, 3> position = particle.getPosition();
    std::array<double, 3> velocity = particle.getVelocity();
    double radius = particle.getRadius();

    for(Box& box : m_boxes) {
        // Check for collision on box X-sides
        if (position[0] < box.m_origin[0] + radius) {
            particle.setX(box.m_origin[0] + radius);
            particle.setVX(-velocity[0] * m_config.coefficientRestitution);
        } else if (position[0] > box.m_origin[0] + box.m_length - radius) {
            particle.setX(box.m_origin[0] + box.m_length - radius);
            particle.setVX(-velocity[0] * m_config.coefficientRestitution);
        }
        // Check for collision on box Y-sides
        if (position[1] < box.m_origin[1] + radius) {
            particle.setY(box.m_origin[1] + radius);
            particle.setVY(-velocity[1] * m_config.coefficientRestitution);
        } else if (position[1] > box.m_origin[1] + box.m_height - radius) {
            particle.setY(box.m_origin[1] + box.m_height - radius);
            particle.setVY(-velocity[1] * m_config.coefficientRestitution);
        }
        // Check for collision on box Z-sides
        if (position[2] < box.m_origin[2] + radius) {
            particle.setZ(box.m_origin[2] + radius);
            particle.setVZ(-velocity[2] * m_config.coefficientRestitution);
        } else if (position[2] > box.m_origin[2] + box.m_depth - radius) {
            particle.setZ(box.m_origin[2] + box.m_depth - radius);
            particle.setVZ(-velocity[2] * m_config.coefficientRestitution);
        }
    }
}

std::vector<Particle>& Universe::getParticles() {
    return m_particles;
}

void Universe::toggleGravity() {
    m_applyGravity = !m_applyGravity;
}

bool Universe::getIsGravity() {
    return m_applyGravity;
}