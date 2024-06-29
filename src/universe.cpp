#include "universe.h"
#include "renderer.hpp"

Universe::Universe(const Config& config)
    : particles(config.particles),
      box(config.box),
      circle(config.circle),
      coefficientRestitution(config.coefficientRestitution),
      deltaTime(config.deltaTime),
      simulationTime(config.simulationTime),
      applyGravity(config.applyGravity),
      globalAcceleration(config.globalAcceleration),
      scaleFactorPixels(config.scaleFactorPixels)
      {}

void Universe::runAndRender(const std::string& dataFileName) {

    std::ofstream file;
    if (!dataFileName.empty()) {
        file.open(dataFileName);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << dataFileName << std::endl;
            return;
        }
    }

    int stepNumber = 0;

    
    // Apply global acceleration
    applyAccelerationToParticles(globalAcceleration);

    // Set window size
    int windowLength = std::floor(scaleFactorPixels * box.getLength());
    int windowHeight = std::floor(scaleFactorPixels * box.getHeight());

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    
    sf::RenderWindow window(sf::VideoMode(windowLength, windowHeight), "Verlet", sf::Style::None, settings);

    Renderer renderer(window, box, scaleFactorPixels);

    // Set SFML Clock
    sf::Clock clock;
    
    // // Main loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if(clock.getElapsedTime().asSeconds() > runTime){
            makeStep();
            saveStep(file, stepNumber);
            window.clear(sf::Color::Black);
            renderer.render(*this);
            window.display();
            stepNumber++;
        }
    }
    if (file.is_open()) {file.close();}
}

void Universe::makeStep(){
    
    // Apply Newton's law of universal gravitation
    if(applyGravity){computeGravitationalForces();}
    
    for (Particle& particle : particles) {
        // Update particle
        particle.update(deltaTime);

        // Handle box collisions
        handleBoxCollision(particle, coefficientRestitution);

        // Handle circle collisions if circle radius isn't null.
        if (circle.getRadius() != 0) {handleCircleCollision(particle, coefficientRestitution);}
    }
    // Handle particles collisions
    handleParticleCollisions();

    runTime += deltaTime;
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

void Universe::addRndParticle(double maxVelocityX, double maxVelocityY, double minRadius, double maxRadius, double minMass, double maxMass){
    std::array<double, 2> position = {rndNumber(box.getXOrigin(), box.getXMAX()), rndNumber(box.getYOrigin(), box.getYMAX())};
    std::array<double, 2> velocity = {rndNumber(-maxVelocityX, maxVelocityX), rndNumber(-maxVelocityY, maxVelocityY)};
    double radius = rndNumber(minRadius, maxRadius);
    double mass = rndNumber(minMass, maxMass);

    Particle particle(position, velocity, radius, mass);
    particles.push_back(particle);
}

void Universe::applyAccelerationToParticles(std::array<double, 2> &globalAcceleration){
        for (Particle& particle : particles){
            std::array<double, 2> acceleration = particle.getAcceleration();
            particle.setAcceleration(acceleration + globalAcceleration);
        }
    }

void Universe::computeGravitationalForces() {
    
    for (size_t i = 0; i < particles.size(); ++i) {
         // Reset acceleration to global acceleration
        particles[i].setAcceleration(globalAcceleration);

        for (size_t j = 0; j < particles.size(); ++j) {
            if (i != j) {
                std::array<double, 2> forceDirection = particles[j].getPosition() - particles[i].getPosition();
                double distance = getMagnitude(forceDirection);
                if (distance > 0) {
                    double forceMagnitude = G * particles[i].getMass() * particles[j].getMass() / (distance * distance);
                    
                    // Divide by distance in order to normalize forceDirection
                    std::array<double, 2> force = forceDirection * (forceMagnitude / distance);
                    
                    // Add force to acceleration (divide by mass because 2nd Newton's law).
                    particles[i].setAcceleration(particles[i].getAcceleration() + force * (1 / particles[i].getMass()));
                }
            }
        }
    }
}

void Universe::handleParticleCollisions() {
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            Particle& p1 = particles[i];
            Particle& p2 = particles[j];
            
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
                p1.setVelocity(v1 + impulse * m2 * distanceVectorNormalized * coefficientRestitution);
                p2.setVelocity(v2 - impulse * m1 * distanceVectorNormalized * coefficientRestitution);
            }
        }
    }
}

void Universe::handleBoxCollision(Particle &particle, double coefficientRestitution){

    // Left collision
    if(particle.getX() < box.getXOrigin() + particle.getRadius()){
        particle.setX(box.getXOrigin() + particle.getRadius());
        particle.setVX(-particle.getVX()*coefficientRestitution);
    }
    // Right collision
    if(particle.getX() > box.getXMAX() - particle.getRadius()){
        particle.setX(box.getXMAX() - particle.getRadius());
        particle.setVX(-particle.getVX()*coefficientRestitution);
    }
    // Down collision
    if(particle.getY() < box.getYOrigin() + particle.getRadius()){
        particle.setY(box.getYOrigin() + particle.getRadius());
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

// Getter for circle
Circle Universe::getCircle() const {
    return circle;
}

// Getter for box
Box Universe::getBox() const {
    return box;
}

// Getter for particles vector
std::vector<Particle> const& Universe::getParticles() const{
    return particles;
}

// Getter for display runTime in renderer
double Universe::getRunTime() const{
    return runTime;
}