#ifndef ZOOMANAGEMENT_ANIMAL_H
#define ZOOMANAGEMENT_ANIMAL_H

#include <string>

class Animal {
protected:
    int age;
    std::string gender;
    std::string birthSeason;
    std::string color;
    double weight;
    std::string origin;
    std::string species;

public:
    Animal(int age, const std::string& gender, const std::string& birthSeason,
          const std::string& color, double weight, const std::string& origin,
          const std::string& species);
    
    virtual ~Animal() = default;
    virtual std::string getDescription() const;
    int getAge() const { return age; }
    std::string getGender() const { return gender; }
    std::string getBirthSeason() const { return birthSeason; }
    std::string getColor() const { return color; }
    double getWeight() const { return weight; }
    std::string getOrigin() const { return origin; }
    std::string getSpecies() const { return species; }
};

#endif //ZOOMANAGEMENT_ANIMAL_H
