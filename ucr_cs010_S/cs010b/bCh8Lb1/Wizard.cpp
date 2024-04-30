#include <iostream>
#include <ostream>
#include <string>

#include "Wizard.h"

using namespace std;

Wizard::Wizard(const string &name, double health, double attackStrength, int rank) : Character(WIZARD, name, health, attackStrength), rank(rank){}

void Wizard::attack(Character &oppo){
    if(oppo.getType() == type)
    {
        Wizard &opp = dynamic_cast<Wizard &>(oppo);
        string name = getName();
        double damage = ((static_cast<double>(this->rank) / static_cast<double>(opp.rank)) * this->attackStrength);
        oppo.damage(damage);
        cout << "Wizard " << this->name << " attacks " << oppo.getName() << " --- POOF!!" << endl;
        cout << oppo.getName() << " takes " << damage << " damage." << endl;
    }
    else{
        string name = getName();
        double damage = attackStrength;
        oppo.damage(damage);
        cout << "Wizard " << this->name << " attacks " << oppo.getName() << " --- POOF!!" << endl;
        cout << oppo.getName() << " takes " << damage << " damage." << endl;
    }
}