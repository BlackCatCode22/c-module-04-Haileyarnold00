#ifndef HYENA_H
#define HYENA_H

#include "Animal.h"

class Hyena : public Animal {
public:
    Hyena(int age, const std::string& gender, const std::string& birthSeason,
          const std::string& color, double weight, const std::string& origin);
};

#endif //HYENA_H
