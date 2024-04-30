#include <iostream>

using namespace std;

#include "Distance.h"

Distance::Distance(){
    _feet = 0;
    _inches = 0;
}

Distance::Distance(unsigned ft, double in){
    _feet = ft;
    _inches = in;
    init();
}

Distance::Distance(double in){
    _feet = 0;
    _inches = in;
    init();
}

unsigned Distance::getFeet() const{
    return _feet;
}

double Distance::getInches() const{
    return _inches;
}

double Distance::distanceInInches() const {
    double totalInch;
    totalInch = (_feet * 12) + _inches;
    return totalInch;
}

double Distance::distanceInFeet() const{
    double totalFeet;
    totalFeet = (_inches / 12) + _feet;
    return totalFeet;
}

double Distance::distanceInMeters() const{
    double meters;
    meters = _feet * 12 + _inches;
    meters = meters * 0.0254;
    return meters; 
}

Distance Distance::operator+(const Distance &rhs) const{
    Distance sum;

    double feetCalc;
    int feet;

    feetCalc = distanceInInches() + rhs.distanceInInches();
    feet = feetCalc / 12;

    sum._inches = feetCalc - (feet * 12);
    sum._feet = static_cast<double>(feet);

    return sum;
}

Distance Distance::operator-(const Distance &rhs) const{
    Distance difference;

    double feetCalc;
    int feet;


    feetCalc = distanceInInches() - rhs.distanceInInches();
    if(feetCalc < 0)
    {
        feetCalc = feetCalc * -1;
    }
    feet = feetCalc / 12;

    difference._inches = feetCalc - (feet * 12);
    difference._feet = static_cast<double>(feet);

    return difference;
}

 ostream & operator<<(ostream &out, const Distance &rhs){
    out << rhs._feet << "' " << rhs._inches << "\"";
    return out;
}

void Distance::init(){
    if(_inches < 0)
    {
        _inches = _inches * -1;
    }

    while(_inches >= 12)
    {
        ++_feet;
        _inches = _inches - 12;
    }

}