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

float time_counter = 0.0;

std::array<int, 3> getRainbow() {
    time_counter += 0.1f;
    
    const float r = sin(time_counter);
    const float g = sin(time_counter + 0.33f * 2.0f * M_PI);
    const float b = sin(time_counter + 0.66f * 2.0f * M_PI);
    
    return {static_cast<int>(255.0f * r * r),
            static_cast<int>(255.0f * g * g),
            static_cast<int>(255.0f * b * b)};
}