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

void Universe::addRndParticle(double maxVelocity, double minRadius, double maxRadius){
    std::array<double, 2> position = {rndNumber(box.getXMIN(), box.getXMAX()), rndNumber(box.getYMIN(), box.getYMAX())};
    std::array<double, 2> velocity = {rndNumber(-maxVelocity, maxVelocity), rndNumber(-maxVelocity, maxVelocity)};
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
