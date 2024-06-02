#include "utils.h"
#include <random>

double rndNumber(double min, double max) {
    static std::random_device rd;  // Obtient une graine initiale à partir du matériel
    static std::mt19937 gen(rd()); // Initialise le générateur avec la graine

    // Définir une distribution uniforme entre min et max
    std::uniform_real_distribution<> dis(min, max);
    
    // Générer et retourner le nombre aléatoire
    return dis(gen);
}