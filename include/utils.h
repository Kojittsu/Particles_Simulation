#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <iomanip>
#include <sstream>
#include "array.h"

double rndNumber(double min, double max);

std::string formatedTime(double seconds);

std::array<int, 3> getRainbow();

#endif
