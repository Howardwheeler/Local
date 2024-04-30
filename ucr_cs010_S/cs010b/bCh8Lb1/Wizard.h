#include <iostream>
#include <ostream>
#include <string>

#include "Character.h"

#ifndef __WIZARD_H__
#define __WIZARD_H__

using namespace std;

class Wizard : public Character {
    public:
        Wizard(const string& name, double health, double attackStrength, int rank);
        void attack(Character& oppo);
    private:
        int rank;
};
#endif