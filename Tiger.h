#ifndef TIGER_H
#define TIGER_H

#include "Animal.h"

class Tiger : public Animal {
public:
    Tiger(int age, const std::string& gender, const std::string& birthSeason,
          const std::string& color, double weight, const std::string& origin);
};

#endif //TIGER_H
