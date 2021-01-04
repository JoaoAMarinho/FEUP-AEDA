#include "zoo.h"
#include <iostream>
#include <stdlib.h>
#include<sstream>
using namespace std;

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1){
    animals.push_back(a1);
}

string Zoo::getInfo () const{
    string result;
    for (auto iter = animals.begin(); iter != animals.end() ; ++iter) {
        result+=(*iter)->getInfo()+"\n";
    }
    return result;
}

bool Zoo::isYoung(string nameA){
    for (auto iter = animals.begin(); iter != animals.end() ; ++iter) {
        if ((*iter)->getName()==nameA&&(*iter)->isYoung()) return true;
    }
    return false;
}

void Zoo::allocateVeterinarians(istream &isV){
    string name;
    string code;
    while(getline(isV,name)){
        getline(isV,code);
        stringstream ss(code);
        long codeNum;
        ss>>codeNum;
        Veterinary *vet=new Veterinary(name,codeNum);
        veterinarians.push_back(vet);
    }
    for (int i = 0; i < animals.size(); ++i) {
        (*animals[i]).setVeterinary(veterinarians[i%veterinarians.size()]);
    }
}

bool Zoo::removeVeterinary (string nameV){
    for (int i = 0; i < veterinarians.size(); ++i) {
        if ((veterinarians[i])->getName()==nameV) {
            for (auto iter = animals.begin(); iter !=animals.end() ; ++iter) {
                if ((*iter)->getVeterinary()==veterinarians[i]){
                    (*iter)->setVeterinary(veterinarians[(i+1)%veterinarians.size()]);
                }
            }
            veterinarians.erase(veterinarians.begin()+i);
            return true;
        }
    }
    return false;
}

bool Zoo::operator < (Zoo& zoo2) const{
    int sumAge1=0, sumAge2=0;
    for (auto iter = animals.begin(); iter != animals.end() ; ++iter) {
        sumAge1+=(*iter)->getAge();
    }
    for (auto iter = zoo2.animals.begin(); iter != zoo2.animals.end() ; ++iter) {
        sumAge2+=(*iter)->getAge();
    }
    if (sumAge1<sumAge2) return true;
    else return false;
}