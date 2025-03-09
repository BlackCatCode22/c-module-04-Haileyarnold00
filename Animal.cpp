#include "Animal.h"
#include <sstream>
#include <iomanip>

Animal::Animal(int age, const std::string& gender, const std::string& birthSeason,
               const std::string& color, double weight, const std::string& origin,
               const std::string& species)
    : age(age), gender(gender), birthSeason(birthSeason), color(color),
      weight(weight), origin(origin), species(species) {}

std::string Animal::getDescription() const {
    std::ostringstream description;
    description << age << " year old " << gender << " " << species;
    
    if (birthSeason == "unknown") {
        description << ", unknown birth season";
    } else {
        description << ", born in " << birthSeason;
    }
    
    description << ", " << color << " color"
               << ", weighing " << std::fixed << std::setprecision(2) << weight << " pounds"
               << ", from " << origin;
    
    return description.str();
}
