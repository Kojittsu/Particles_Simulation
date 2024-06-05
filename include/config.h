#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "particle.h"
#include "box.h"
#include "circle.h"

struct Config {
    std::vector<Particle> particles;
    Box box = Box();
    Circle circle = Circle();
    double deltaTime;
    int stepNumbers;
    double coefficientRestitution;
    int scaleFactorPixels;
};

bool readConfig(const std::string& filename, Config& config);

#endif // CONFIG_H
