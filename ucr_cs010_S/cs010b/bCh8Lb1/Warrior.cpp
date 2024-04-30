#include <iostream>
#include <ostream>
#include <string>

#include "Warrior.h"

using namespace std;

Warrior::Warrior(const string &name, double health, double attackStrength, const string &group) : Character(WARRIOR, name, health, attackStrength), group(group){}

void Warrior::attack(Character &oppo){
    if(oppo.getType() == type)
    {
        Warrior &opp = dynamic_cast<Warrior &>(oppo);
        if(opp.type == this->type && this->group == opp.group)
        {
            cout << "Warrior " << this->name << " does not attack Warrior " << oppo.getName() << "." << endl;
            cout << "They share an allegiance with " << group << "." << endl;
            return;
        }
        else{
            string name = getName();
            double damage = ((health/MAX_HEALTH) * this->attackStrength);
            oppo.damage(damage);
            cout << "Warrior " << this->name << " attacks " << oppo.getName() << " --- SLASH!!" << endl;
            cout << oppo.getName() << " takes " << damage << " damage." << endl;
        }
    }
    else{
        string name = getName();
        double damage = ((health/MAX_HEALTH) * this->attackStrength);
        oppo.damage(damage);
        cout << "Warrior " << this->name << " attacks " << oppo.getName() << " --- SLASH!!" << endl;
        cout << oppo.getName() << " takes " << damage << " damage." << endl;
    }
}