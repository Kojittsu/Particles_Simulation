#include "config.h"

bool readConfig(const std::string& filename, Config& config) {
    try {
        YAML::Node yaml = YAML::LoadFile(filename);

        // Load renderer parameters
        config.rendererConfig.speedFactor       = yaml["renderer"]["speedFactor"].as<double>();
        config.rendererConfig.scaleFactor       = yaml["renderer"]["scaleFactor"].as<double>();

        // Load universe parameters
        config.universeConfig.deltaTime              = yaml["universe"]["deltaTime"].as<double>();
        config.universeConfig.applyGravity           = yaml["universe"]["applyGravity"].as<bool>();
        config.universeConfig.globalAcceleration     = yaml["universe"]["globalAcceleration"].as<std::array<double, 3>>();
        config.universeConfig.coefficientRestitution = yaml["universe"]["coefficientRestitution"].as<double>();
        config.universeConfig.dataFileName           = yaml["universe"]["dataFileName"].as<std::string>();

        // Check renderer config validity
        if (config.rendererConfig.speedFactor <= 0) {
            throw std::invalid_argument("Invalid config : speed factor value must be > 0");
        }
        if (config.rendererConfig.scaleFactor <= 0) {
            throw std::invalid_argument("Invalid config : scale factor value must be > 0");
        }

        // Check universe config validity
        if (config.universeConfig.deltaTime <= 0) {
            throw std::invalid_argument("Invalid config : delta time value must be > 0");
        }
        if (config.universeConfig.coefficientRestitution < 0.0 || config.universeConfig.coefficientRestitution > 1.0) {
            throw std::invalid_argument("Invalid config : coefficient restitution value must be in [0,1]");
        }

        // Load particles
        for (const auto& particleNode : yaml["particles"]) {
            std::array<double, 3> position = particleNode["position"].as<std::array<double, 3>>();
            std::array<double, 3> velocity = particleNode["velocity"].as<std::array<double, 3>>();
            double radius                  = particleNode["radius"].as<double>();
            double mass                    = particleNode["mass"].as<double>();
            std::array<float, 3> color     = particleNode["color"].as<std::array<float, 3>>();
            std::string name               = particleNode["name"].as<std::string>();

            // Check particle validity
            if (radius <= 0.0) {
                throw std::invalid_argument("Invalid particle: radius must be > 0");
            }
            if (mass <= 0.0) {
                throw std::invalid_argument("Invalid particle: mass must be > 0");
            }
            for (int c : color) {
                if (c < 0 || c > 1) {
                    throw std::invalid_argument("Invalid particle: color components must be in [0,1]");
                }
            }

            Particle particle(position, velocity, config.universeConfig.globalAcceleration, radius, mass, color, name);
            config.universeConfig.particles.push_back(particle);
        }

        // Load boxes
        for (const auto& particleNode : yaml["boxes"]) {
            std::array<double, 3> origin = particleNode["origin"].as<std::array<double, 3>>();
            double length = particleNode["length"].as<double>();
            double height = particleNode["height"].as<double>();
            double depth = particleNode["depth"].as<double>();

            Box box(origin, length, height, depth);
            config.universeConfig.boxes.push_back(box);

            // Check box validity
            if (length <= 0) {
                throw std::invalid_argument("Box length must be > 0");
            }
            if (height <= 0) {
                throw std::invalid_argument("Box height must be > 0");
            }
            if (depth <= 0) {
                throw std::invalid_argument("Box depth must be > 0");
            }
        }

        return true;
    }
    catch (const YAML::Exception& e) {
        std::cerr << "YAML exception occured when reading '" << filename << "' : " << e.what() << std::endl;
        return false;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid_argument exception occured when reading '" << filename << "': " << e.what() << std::endl;
        return false;
    }
}
