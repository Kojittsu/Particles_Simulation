#include "universe.h"

// Constructor
Universe::Universe(const UniverseConfig& universeConfig)
    :
        config_(universeConfig),
        particles_(universeConfig.particles),
        boxes_(universeConfig.boxes),
        applyGravity_(universeConfig.applyGravity),
        globalAcceleration_(universeConfig.globalAcceleration)
{
    // Open dataFile if dataFileName provided
    if (!config_.dataFileName.empty()) {
        logFile_.open(config_.dataFileName);
        if (!logFile_.is_open()) {
            std::cerr << "Error opening file: " << config_.dataFileName << std::endl;
        }
    }
    applyAccelerationToParticles(globalAcceleration_);
}

Universe::~Universe() {
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

void Universe::makeStep() {
    // Apply Newton's law of universal gravitation
    if(applyGravity_) {
        computeGravitationalForces();
    }

    for (Particle& particle : particles_) {
        // Update particle
        particle.update(config_.deltaTime);
        // Handle boxes collisions
        computeBoxesCollision(particle);
    }

    computeParticleCollisions();

    simuationTime_ += config_.deltaTime;

    // Save universe current step
    if (logFile_.is_open()) {
        saveStep(logFile_);
    }
}

void Universe::saveStep(std::ofstream& file) {
    int particleNumber = 1;
    for (const Particle& particle : particles_) {
        file << simuationTime_ << "," << particleNumber << "," << particle.getX() << "," << particle.getY() << "," << particle.getZ() << "\n";
        ++particleNumber;
    }
}

void Universe::addParticle(Particle& particle) {
    // Reset acceleration to global acceleration
    particle.setAcceleration(globalAcceleration_);

    particles_.push_back(particle);
}


void Universe::applyAccelerationToParticles(const std::array<double, 3>& accelerationContribution) {
    for (Particle& particle : particles_){
        particle.setAcceleration(particle.getAcceleration() + accelerationContribution);
    }
}

void Universe::computeGravitationalForces() {
    for (Particle& particle : particles_) {
        // Reset acceleration to global acceleration
        particle.setAcceleration(globalAcceleration_);
    }

    for (size_t i = 0; i < particles_.size(); ++i) {
        for (size_t j = i + 1; j < particles_.size(); ++j) {
            Particle& p1 = particles_[i];
            Particle& p2 = particles_[j];

            std::array<double, 3> forceDirection = p2.getPosition() - p1.getPosition();
            double distance = getMagnitude(forceDirection);
            if (distance > 0) {
                double forceMagnitude = G_ * p1.getMass() * p2.getMass() / (distance * distance);
                std::array<double, 3> force = forceDirection * (forceMagnitude / distance);

                // Apply Newton's second law
                p1.setAcceleration(p1.getAcceleration() + force * (1 / p1.getMass()));
                p2.setAcceleration(p2.getAcceleration() - force * (1 / p2.getMass()));
            }
        }
    }
}

void Universe::computeParticleCollisions() {
    for (size_t i = 0; i < particles_.size(); ++i) {
        for (size_t j = i + 1; j < particles_.size(); ++j) {
            Particle& p1 = particles_[i];
            Particle& p2 = particles_[j];

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

                p1.setVelocity(v1 + impulse * m2 * distanceVectorNormalized * config_.coefficientRestitution);
                p2.setVelocity(v2 - impulse * m1 * distanceVectorNormalized * config_.coefficientRestitution);
            }
        }
    }
}

void Universe::computeBoxesCollision(Particle& particle) {
    std::array<double, 3> position = particle.getPosition();
    std::array<double, 3> velocity = particle.getVelocity();
    double radius = particle.getRadius();

    for(Box& box : boxes_) {
        // Check for collision on box X-sides
        if (position[0] < box.origin_[0] + radius) {
            particle.setX(box.origin_[0] + radius);
            particle.setVX(-velocity[0] * config_.coefficientRestitution);
        } else if (position[0] > box.origin_[0] + box.length_ - radius) {
            particle.setX(box.origin_[0] + box.length_ - radius);
            particle.setVX(-velocity[0] * config_.coefficientRestitution);
        }
        // Check for collision on box Y-sides
        if (position[1] < box.origin_[1] + radius) {
            particle.setY(box.origin_[1] + radius);
            particle.setVY(-velocity[1] * config_.coefficientRestitution);
        } else if (position[1] > box.origin_[1] + box.height_ - radius) {
            particle.setY(box.origin_[1] + box.height_ - radius);
            particle.setVY(-velocity[1] * config_.coefficientRestitution);
        }
        // Check for collision on box Z-sides
        if (position[2] < box.origin_[2] + radius) {
            particle.setZ(box.origin_[2] + radius);
            particle.setVZ(-velocity[2] * config_.coefficientRestitution);
        } else if (position[2] > box.origin_[2] + box.depth_ - radius) {
            particle.setZ(box.origin_[2] + box.depth_ - radius);
            particle.setVZ(-velocity[2] * config_.coefficientRestitution);
        }
    }
}

std::vector<Particle>& Universe::getParticles() {
    return particles_;
}

std::vector<Box>& Universe::getBoxes() {
    return boxes_;
}

void Universe::toggleGravity() {
    applyGravity_ = !applyGravity_;
}

bool Universe::getIsGravity() {
    return applyGravity_;
}
