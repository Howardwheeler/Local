#include <iostream>
#include <ostream>
#include <string>

#include "Elf.h"

using namespace std;

Elf::Elf(const string &name, double health, double attackStrength, const string& group) : Character(ELF, name, health, attackStrength), group(group){}

void Elf::attack(Character &oppo){
    if(oppo.getType() == type)
    {
        Elf &opp = dynamic_cast<Elf &>(oppo);
        if(opp.type == this->type && this->group == opp.group)
        {
            cout << "Elf " << this->name << " does not attack Elf " << oppo.getName() << "." << endl;
            cout << "They are both members of the " << group << " family." <<endl;
            return;
        }
        else{
            string name = getName();
            double damage = ((health/MAX_HEALTH) * this->attackStrength);
            oppo.damage(damage);
            cout << "Elf " << this->name << " shoots an arrow at " << oppo.getName() << " --- TWANG!!" << endl;
            cout << oppo.getName() << " takes " << damage << " damage." << endl;
        }
    }
    else{
        string name = getName();
        double damage = ((health/MAX_HEALTH) * this->attackStrength);
        oppo.damage(damage);
        cout << "Elf " << this->name << " shoots an arrow at " << oppo.getName() << " --- TWANG!!" << endl;
        cout << oppo.getName() << " takes " << damage << " damage." << endl;
    }
}