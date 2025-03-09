#include "Tiger.h"

Tiger::Tiger(int age, const std::string& gender, const std::string& birthSeason,
             const std::string& color, double weight, const std::string& origin)
    : Animal(age, gender, birthSeason, color, weight, origin, "tiger") {}
