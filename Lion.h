#ifndef LION_H
#define LION_H

#include "Animal.h"

class Lion : public Animal {
public:
    Lion(int age, const std::string& gender, const std::string& birthSeason,
         const std::string& color, double weight, const std::string& origin);
};

#endif //LION_H
