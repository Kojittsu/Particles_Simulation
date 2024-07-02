#include "universe.h"
#include "renderer.hpp"

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
        for(int i=0; i< config.rndParticle_numbers; i++){
            addRndParticle(config.rndParticle_maxVelocityX, config.rndParticle_maxVelocityY, config.rndParticle_minRadius, config.rndParticle_maxRadius, config.rndParticle_minMass, config.rndParticle_maxMass);
        }
        applyAccelerationToParticles(m_globalAcceleration);
      }

void Universe::makeStep(){
    
    // Apply Newton's law of universal gravitation
    if(m_applyGravity){computeGravitationalForces();}
    
    for (Particle& particle : m_particles) {
        // Update particle
        particle.update(m_deltaTime);

        // Handle box collisions
        handleBoxCollision(particle);

        // Handle circle collisions if circle radius isn't null.
        if (m_circleRadius != 0) {handleCircleCollision(particle);}
    }
    // Handle particles collisions
    handleParticleCollisions();

    // Update runtime
    m_runTime += m_deltaTime;
}

void Universe::saveStep(std::ofstream &file, int stepNumber){
    double currentTime = stepNumber * m_deltaTime;
    int particleNumber = 1;
    for (Particle& particle : m_particles){
        if (file.is_open()) {
            file << currentTime << "," << particleNumber << "," << particle.getX() << "," << particle.getY() << "\n";
        }
        particleNumber++;
    }
}

void Universe::addParticle(Particle &particle){
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

void Universe::applyAccelerationToParticles(const std::array<double, 2> &accelerationContribution){
        for (Particle& particle : m_particles){
            std::array<double, 2> acceleration = particle.getAcceleration();
            particle.setAcceleration(acceleration + accelerationContribution);
        }
    }

void Universe::computeGravitationalForces() {
    
    for (size_t i = 0; i < m_particles.size(); ++i) {
         // Reset acceleration to global acceleration
        m_particles[i].setAcceleration(m_globalAcceleration);

        for (size_t j = 0; j < m_particles.size(); ++j) {
            if (i != j) {
                std::array<double, 2> forceDirection = m_particles[j].getPosition() - m_particles[i].getPosition();
                double distance = getMagnitude(forceDirection);
                if (distance > 0) {
                    double forceMagnitude = m_G * m_particles[i].getMass() * m_particles[j].getMass() / (distance * distance);
                    
                    // Divide by distance in order to normalize forceDirection
                    std::array<double, 2> force = forceDirection * (forceMagnitude / distance);
                    
                    // Add force to acceleration (divide by mass because 2nd Newton's law).
                    m_particles[i].setAcceleration(m_particles[i].getAcceleration() + force * (1 / m_particles[i].getMass()));
                }
            }
        }
    }
}

void Universe::handleParticleCollisions() {
    for (size_t i = 0; i < m_particles.size(); ++i) {
        for (size_t j = i + 1; j < m_particles.size(); ++j) {
            Particle& p1 = m_particles[i];
            Particle& p2 = m_particles[j];
            
            // Calculate collision vector beetwen 2 particles
            std::array<double, 2> distanceVector = p1.getPosition() - p2.getPosition();

            // Calculate distance beetwen 2 particles
            double distance = getMagnitude(distanceVector);
            
            double minDistance = p1.getRadius() + p2.getRadius();

            // Check if particles collide
            if (distance < minDistance) {
                // Normalize collision vector
                std::array<double, 2> distanceVectorNormalized = distanceVector * (1/distance);

                // Move particles so they don't overlap anymore
                double overlap = minDistance - distance;
                p1.setPosition(p1.getPosition() + distanceVectorNormalized * (overlap / 2));
                p2.setPosition(p2.getPosition() - distanceVectorNormalized * (overlap / 2));

                // Get velocities
                std::array<double, 2> v1 = p1.getVelocity();
                std::array<double, 2> v2 = p2.getVelocity();

                // Calculate relative velocity in normal direction
                std::array<double, 2> diffVelocity = v2 - v1;
                double relativeVelocity = dotProduct(diffVelocity, distanceVectorNormalized);

                // Get masses
                double m1 = p1.getMass();
                double m2 = p2.getMass();
                double massSum = m1 + m2;

                // Calculate collision impulsion
                double impulse = (2 * relativeVelocity) / massSum;

                // Update particle velocities taking into account mass and coefficient of restitution
                p1.setVelocity(v1 + impulse * m2 * distanceVectorNormalized * m_coefficientRestitution);
                p2.setVelocity(v2 - impulse * m1 * distanceVectorNormalized * m_coefficientRestitution);
            }
        }
    }
}

void Universe::handleBoxCollision(Particle &particle){

    // Left collision
    if(particle.getX() < m_boxOriginX + particle.getRadius()){
        particle.setX(m_boxOriginX + particle.getRadius());
        particle.setVX(-particle.getVX() * m_coefficientRestitution);
    }
    // Right collision
    if(particle.getX() > m_boxOriginX + m_boxLength - particle.getRadius()){
        particle.setX(m_boxOriginX + m_boxLength - particle.getRadius());
        particle.setVX(-particle.getVX() * m_coefficientRestitution);
    }
    // Down collision
    if(particle.getY() < m_boxOriginY + particle.getRadius()){
        particle.setY(m_boxOriginY + particle.getRadius());
        particle.setVY(-particle.getVY() * m_coefficientRestitution);
    }
    // Up collision
    if(particle.getY() > m_boxOriginY + m_boxHeight - particle.getRadius()){
        particle.setY(m_boxOriginY + m_boxHeight - particle.getRadius());
        particle.setVY(-particle.getVY() * m_coefficientRestitution);
    }
}

void Universe::handleCircleCollision(Particle &particle){
    // Calculate distance beetwen particle and circle center
    double dx = particle.getX() - m_circleX;
    double dy = particle.getY() - m_circleY;
    double distance = sqrt(dx * dx + dy * dy);
    
    // Check if particle collide with circle
    if (distance > m_circleRadius - particle.getRadius()) {
        // Normalize collision vector
        double nx = dx / distance;
        double ny = dy / distance;

        // Move particle to the circle surface
        particle.setX(m_circleX + nx * (m_circleRadius - particle.getRadius()));
        particle.setY(m_circleY + ny * (m_circleRadius - particle.getRadius()));

        // Calculate particle velocity in the normal direction
        double dotProduct = particle.getVX() * nx + particle.getVY() * ny;

        // Calculate the normal component of velocity
        double vnx = dotProduct * nx;
        double vny = dotProduct * ny;

        // Reverse the normal component of the velocity and apply the coefficient of restitution
        double newVx = particle.getVX() - 2 * vnx * m_coefficientRestitution;
        double newVy = particle.getVY() - 2 * vny * m_coefficientRestitution;

        // Update particle velocity
        particle.setVX(newVx);
        particle.setVY(newVy);
    }
}

// Getter for particles vector
std::vector<Particle> const& Universe::getParticles() const{
    return m_particles;
}