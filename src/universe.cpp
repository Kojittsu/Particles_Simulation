#include "universe.h"

Universe::Universe(const Config& config)
    : particles(config.particles), box(config.box), circle(config.circle), coefficientRestitution(config.coefficientRestitution), deltaTime(config.deltaTime), stepNumbers(config.stepNumbers) {}

void Universe::run(const std::string& filename) {
    std::ofstream file;
    if (!filename.empty()) {
        file.open(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }
    }

    for (int stepNumber = 0; stepNumber < stepNumbers; ++stepNumber) {
        makeStep();
        saveStep(file, stepNumber);
    }

    if (file.is_open()) {file.close();}
}

void Universe::makeStep(){
    for (Particle& particle : particles) {
        particle.update(deltaTime);
        // handleBoxCollision(particle, coefficientRestitution);
        handleCircleCollision(particle, coefficientRestitution);
    }
    handleParticleCollisions(coefficientRestitution);
}

void Universe::saveStep(std::ofstream &file, int stepNumber){
    double currentTime = stepNumber * deltaTime;
    int particleNumber = 1;
    for (Particle& particle : particles){
        if (file.is_open()) {
            file << currentTime << "," << particleNumber << "," << particle.getX() << "," << particle.getY() << "\n";
        }
        particleNumber += 1;
    }
}

void Universe::addParticle(Particle &particle){
    particles.push_back(particle);
}

void Universe::addRndParticle(double maxVelocityX, double maxVelocityY, double minRadius, double maxRadius){
    std::array<double, 2> position = {rndNumber(box.getXMIN(), box.getXMAX()), rndNumber(box.getYMIN(), box.getYMAX())};
    std::array<double, 2> velocity = {rndNumber(-maxVelocityX, maxVelocityX), rndNumber(-maxVelocityY, maxVelocityY)};
    std::array<double, 2> acceleration = {0.0, 0.0};

    Particle particle(position, velocity, acceleration, rndNumber(minRadius, maxRadius));
    particles.push_back(particle);
}

std::vector<double> Universe::getParticlesRadius(){
    std::vector<double> particlesRadius;
    for (Particle& particle : particles){
        particlesRadius.push_back(particle.getRadius());
    }
    return particlesRadius;
}

void Universe::handleParticleCollisions(double coefficientRestitution) {
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            Particle& p1 = particles[i];
            Particle& p2 = particles[j];
            
            // Calculate distance beetwen particles
            double dx = p1.getX() - p2.getX();
            double dy = p1.getY() - p2.getY();
            double distance = std::sqrt(dx * dx + dy * dy);
            double minDistance = p1.getRadius() + p2.getRadius();

            // Check if particles collide
            if (distance < minDistance) {
                // Normalize collision vector
                double nx = dx / distance;
                double ny = dy / distance;

                // Move particles so they no longer overlap
                double overlap = minDistance - distance;
                p1.setX(p1.getX() + nx * (overlap / 2));
                p1.setY(p1.getY() + ny * (overlap / 2));
                p2.setX(p2.getX() - nx * (overlap / 2));
                p2.setY(p2.getY() - ny * (overlap / 2));

                // Calculate relative velocities
                double vx1 = p1.getVX();
                double vy1 = p1.getVY();
                double vx2 = p2.getVX();
                double vy2 = p2.getVY();

                // Calculate relative speed in the normal direction
                double relativeVelocity = (vx2 - vx1) * nx + (vy2 - vy1) * ny;

                // Calculate the collision impulse
                double impulse = (2 * relativeVelocity) / (p1.getRadius() + p2.getRadius());

                // Update particle velocities taking into account the coefficient of restitution
                // We suppose here that radius is proportionnal to mass, so mass was replaced by particles radius.
                p1.setVX(vx1 + impulse * nx * p2.getRadius() * coefficientRestitution);
                p1.setVY(vy1 + impulse * ny * p2.getRadius() * coefficientRestitution);
                p2.setVX(vx2 - impulse * nx * p1.getRadius() * coefficientRestitution);
                p2.setVY(vy2 - impulse * ny * p1.getRadius() * coefficientRestitution);
            }
        }
    }
}

void Universe::handleBoxCollision(Particle &particle, double coefficientRestitution){

    // Left collision
    if(particle.getX() < box.getXMIN() + particle.getRadius()){
        particle.setX(box.getXMIN() + particle.getRadius());
        particle.setVX(-particle.getVX()*coefficientRestitution);
    }
    // Right collision
    if(particle.getX() > box.getXMAX() - particle.getRadius()){
        particle.setX(box.getXMAX() - particle.getRadius());
        particle.setVX(-particle.getVX()*coefficientRestitution);
    }
    // Down collision
    if(particle.getY() < box.getYMIN() + particle.getRadius()){
        particle.setY(box.getYMIN() + particle.getRadius());
        particle.setVY(-particle.getVY()*coefficientRestitution);
    }
    // Up collision
    if(particle.getY() > box.getYMAX() - particle.getRadius()){
        particle.setY(box.getYMAX() - particle.getRadius());
        particle.setVY(-particle.getVY()*coefficientRestitution);
    }
}

void Universe::handleCircleCollision(Particle &particle, double coefficientRestitution){
    // Calculate distance beetwen particle and circle center
    double dx = particle.getX() - circle.getCenterX();
    double dy = particle.getY() - circle.getCenterY();
    double distance = sqrt(dx * dx + dy * dy);
    
    // Check if particle collide with circle
    if (distance > circle.getRadius() - particle.getRadius()) {
        // Normalize collision vector
        double nx = dx / distance;
        double ny = dy / distance;

        // Move particle to the circle surface
        particle.setX(circle.getCenterX() + nx * (circle.getRadius() - particle.getRadius()));
        particle.setY(circle.getCenterY() + ny * (circle.getRadius() - particle.getRadius()));

        // Calculate particle velocity in the normal direction
        double dotProduct = particle.getVX() * nx + particle.getVY() * ny;

        // Calculate the normal component of velocity
        double vnx = dotProduct * nx;
        double vny = dotProduct * ny;

        // Reverse the normal component of the velocity and apply the coefficient of restitution
        double newVx = particle.getVX() - 2 * vnx * coefficientRestitution;
        double newVy = particle.getVY() - 2 * vny * coefficientRestitution;

        // Update particle velocity
        particle.setVX(newVx);
        particle.setVY(newVy);
    }
}
