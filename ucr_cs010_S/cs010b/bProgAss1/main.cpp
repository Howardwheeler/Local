#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void readData(const string &file1, vector<double> &path1, vector<double> &coeff1){
    ifstream inFS;
    inFS.open(file1);
    double num;

    if(!inFS.is_open())
    {
        cout << "Error opening " << file1 << endl;
    }
    else{
        while(inFS >> num)
        {
            path1.push_back(num);
            inFS >> num;
            coeff1.push_back(num);
        }
        inFS.close();
    }
}

double interpolation(double input, const vector<double> &path1, const vector<double> &coeff1){
    double a;
    double c;
    double Fa;
    double Fc;
    double coeffFlight;
    bool temp = false;
    for(unsigned int i = 0; i < path1.size(); i++)
    {
        if(path1.at(i) == input)
        {
            temp = true;
            coeffFlight = coeff1.at(i);
        }
    }
    if(temp == true)
    {
        return coeffFlight;
    }
    else{
        for(unsigned int i = 0; i < path1.size(); i++){
            if(path1.at(i) >= input){
                break;
            }
            a = path1.at(i);
            Fa = coeff1.at(i);
        }
        for(unsigned int i = path1.size()-1; i >= 0; i--)
        {
            if(path1.at(i) <= input){
                break;
            }
            c = path1.at(i);
            Fc = coeff1.at(i);
        }
        coeffFlight = Fa + ((input - a)/(c - a))*(Fc - Fa);
        return coeffFlight;
    }
}

bool isOrdered(const vector<double> &path1){
    bool order1 = true;
    for(unsigned int i = 1; i < path1.size(); i++)
    {
        if (path1.at(i) < path1.at(i-1))
        {
            order1 = false;
        }
    }
    return order1;
}

void reorder(vector<double> &path1, vector<double> &coeff1){
    int index1;
    double temp;
    for (unsigned int i = 0; i < path1.size(); i++)
    {
        index1 = i;
        for(unsigned int j = i + 1; j < path1.size(); j++)
        {
            if(path1.at(j) < path1.at(index1))
            {
                index1 = j;
            }
        }
        temp = path1.at(i);
        path1.at(i) = path1.at(index1);
        path1.at(index1) = temp;
        temp = coeff1.at(i);
        coeff1.at(i) = coeff1.at(index1);
        coeff1.at(index1) = temp;
    }
}


int main(int argc, char* argv[]){

    string file1;
    vector<double> path1;
    vector<double> coeff1;
    double input;
    double max;
    double min;
    double temp;
    string userInput;

    file1 = argv[1];

    readData(file1, path1, coeff1);

    if (path1.size() == 0)
    {
        return 1;
    }

    cin >> input;
    if (isOrdered(path1) == false)
    {
        reorder(path1, coeff1);
    }
    min = path1.at(0);
    max = path1.at(path1.size()-1);
    if((input >= min) && (input <= max))
    {
        temp = interpolation(input, path1, coeff1);
        path1.push_back(input);
        coeff1.push_back(temp);
        cout << temp << endl;
    }
    else{
        cout << "input too low or too high" << endl;
    } 

    cin >> userInput;

    while(userInput != "No")
    {
        cin >> input;
        if (isOrdered(path1) == false)
        {
            reorder(path1, coeff1);
        }
        min = path1.at(0);
        max = path1.at(path1.size()-1);
        if((input >= min) && (input <= max))
        {
            temp = interpolation(input, path1, coeff1);
            path1.push_back(input);
            coeff1.push_back(temp);
            cout << temp << endl;
        }
        else{
            cout << "input too low or too high" << endl;
        } 
    cin >> userInput;
    }


}