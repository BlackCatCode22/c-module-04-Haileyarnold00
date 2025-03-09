#ifndef ZOOMANAGEMENT_BEAR_H
#define ZOOMANAGEMENT_BEAR_H

#include "Animal.h"

class Bear : public Animal {
public:
    Bear(int age, const std::string& gender, const std::string& birthSeason,
         const std::string& color, double weight, const std::string& origin);
};

#endif //ZOOMANAGEMENT_BEAR_H
