#include "Hyena.h"

Hyena::Hyena(int age, const std::string& gender, const std::string& birthSeason,
             const std::string& color, double weight, const std::string& origin)
    : Animal(age, gender, birthSeason, color, weight, origin, "hyena") {}
