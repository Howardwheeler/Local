#include <iostream>
#include <ostream>
#include <string>

#include "Character.h"

#ifndef __ELF_H__
#define __ELF_H__

using namespace std;

class Elf : public Character {
    public:
        Elf(const string& name, double health, double attackStrength, const string& group);
        void attack(Character& oppo);
    private:
        string group;
};
#endif