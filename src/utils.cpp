#include "utils.h"

double rndNumber(double min, double max) {
    static std::random_device rd;  // Obtient une graine initiale à partir du matériel
    static std::mt19937 gen(rd()); // Initialise le générateur avec la graine

    // Définir une distribution uniforme entre min et max
    std::uniform_real_distribution<> dis(min, max);
    
    // Générer et retourner le nombre aléatoire
    return dis(gen);
}

std::string formatedTime(double seconds) {
    const int secondsPerMinute = 60;
    const int secondsPerHour = 3600;
    const int secondsPerDay = 86400;
    const int secondsPerYear = 31536000;

    int years = static_cast<int>(seconds) / secondsPerYear;
    seconds = static_cast<int>(seconds) % secondsPerYear;

    int days = static_cast<int>(seconds) / secondsPerDay;
    seconds = static_cast<int>(seconds) % secondsPerDay;

    int hours = static_cast<int>(seconds) / secondsPerHour;
    seconds = static_cast<int>(seconds) % secondsPerHour;

    int minutes = static_cast<int>(seconds) / secondsPerMinute;
    seconds = static_cast<int>(seconds) % secondsPerMinute;

    std::ostringstream oss;
    oss << years << " years, "
        << days << " days, "
        << std::setw(2) << std::setfill('0') << hours << " hours, "
        << std::setw(2) << std::setfill('0') << minutes << " minutes, "
        << std::setw(2) << std::setfill('0') << static_cast<int>(seconds) << " seconds";

    return oss.str();
}