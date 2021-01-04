#include "veterinary.h"
#include <sstream>
using namespace std;

string Veterinary::getName() const {
    return name;
}

long Veterinary::getCode() const{return codOrder;}

Veterinary::Veterinary(string nome, int cod):name(nome),codOrder(cod){}

string Veterinary::getInfo() const {
    stringstream ss;
    string result;
    ss<<"Vet name: "<<name << " / Vet code: "<<codOrder<<endl;
    getline(ss,result);
    return result;
}

