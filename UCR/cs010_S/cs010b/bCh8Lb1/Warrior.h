#include <iostream>
#include <ostream>
#include <string>

#include "Character.h"

#ifndef __WARRIOR_H__
#define __WARRIOR_H__

using namespace std;

class Warrior : public Character {
    public:
        Warrior(const string& name, double health, double attackStrength, const string& group);
        void attack(Character& name);
    private:
        string group;
};
#endif