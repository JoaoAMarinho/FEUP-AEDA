#include "animal.h"

using namespace std;

string Animal::getName() const {
	return name;
}

int Animal::getAge() const {
    return age;
}

void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}

int Animal::youngest=INT_MAX;

Animal::Animal(string name, int age):name(name),age(age){if (age<youngest) youngest=age;
vet= nullptr;}

Dog::Dog(string name, int age, string breed):Animal(name,age),breed(breed){}

Flying::Flying(int maxv, int maxa):maxVelocity(maxv),maxAltitude(maxa){}

Bat::Bat(string name, int age, int maxv, int maxa):Animal(name,age),Flying(maxv,maxa){}

int Animal::getYoungest(){
    return youngest;
}

bool Dog::isYoung ()const{if (age<5)return true;
else return false;}

bool Bat::isYoung ()const{if (age<4)return true;
else return false;}

int Flying::getmaxV() const{return maxVelocity;}

int Flying::getmaxA() const{return maxAltitude;}

string Animal::getInfo() const{
    stringstream ss;
    ss<<name<<", "<< age<<endl;
    if(vet!= nullptr) ss<<", "<<(*vet).getName()<<", "<<(*vet).getCode();
    string info;
    getline(ss,info);
    return info;
}

string Dog::getInfo() const{
    stringstream ss;
    ss<<name<<", "<< age;
    if(vet!= nullptr) ss<<", "<<(*vet).getName()<<", "<<(*vet).getCode();
    ss<<", "<<breed<<endl;
    //ss<<"Name: "<<name<<" / Age: "<< age<<" / Breed: "<<breed<<endl;
    //ss<<(*vet).getInfo();
    string info;
    getline(ss,info);
    return info;
}

string Bat::getInfo() const{
    stringstream ss;
    ss<<name<<", "<< age;
    if(vet!= nullptr) ss<<", "<<(*vet).getName()<<", "<<(*vet).getCode();
    ss<<", "<<getmaxV()<<", "<<getmaxA()<<endl;
    //ss<<"Name: "<<name<<" / Age: "<< age<<" / Max velocity: "<<getmaxV()<<" / Max altitude: "<<getmaxA()<<endl;
    //ss<<(*vet).getInfo();
    string info;
    getline(ss,info);
    return info;
}
