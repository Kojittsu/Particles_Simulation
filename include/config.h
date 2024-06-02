#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "particle.h"
#include "box.h"

struct Config {
    std::vector<Particle> particles;
    Box box = Box();
    double deltaTime;
    int stepNumbers;
    double coefficientRestitution;
};

bool readConfig(const std::string& filename, Config& config);

#endif // CONFIG_H
