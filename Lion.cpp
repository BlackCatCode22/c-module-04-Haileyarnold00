#include "Lion.h"

Lion::Lion(int age, const std::string& gender, const std::string& birthSeason,
           const std::string& color, double weight, const std::string& origin)
    : Animal(age, gender, birthSeason, color, weight, origin, "lion") {}
