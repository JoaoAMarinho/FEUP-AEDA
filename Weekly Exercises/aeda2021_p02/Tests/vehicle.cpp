#include "vehicle.h"
#include <iostream>
#include <utility>

using namespace std;

Vehicle::Vehicle(string b, int m, int y):brand(b),month(m),year(y){}

MotorVehicle::MotorVehicle(string b, int m, int y,string f,int cyl):Vehicle(b,m,y),fuel(f),cylinder(cyl){}

Car::Car(string b, int m, int y, string f, int cyl):MotorVehicle(b,m,y,f,cyl){}

Truck::Truck(string b, int m, int y,string f, int cyl,int ml):MotorVehicle(b,m,y,f,cyl), maximumLoad(ml){}

Bicycle::Bicycle(string b, int m, int y, string t):Vehicle(b,m,y),type(t){}

string Vehicle::getBrand() const{return brand;}

string MotorVehicle::getFuel() const{return fuel;}

int MotorVehicle::getCylinder() const{return cylinder;}

int Vehicle::getYear() const {return year;}

int Vehicle::info() const{
 cout << "Brand - " << brand<<"\nMonth - "<<month<<"\nYear - " << year<<endl;
 return 3;
}

int MotorVehicle::info() const{
    cout << "Brand - " << brand<<"\nMonth - "<<month<<"\nYear - " << year<<"\nFuel - " << fuel<<"\nCylinder - " << cylinder << endl;
    return 5;
}

int Car::info() const{
    return MotorVehicle::info();
}

int Truck::info() const {
    cout << "Brand - " << brand<<"\nMonth - "<<month<<"\nYear - " << year<<"\nFuel - " << getFuel()<<"\nCylinder - " << getCylinder() <<"\nMaximum load - "<<maximumLoad<< endl;
    return 6;
}

int Bicycle::info() const{
    cout << "Brand - " << brand<<"\nMonth - "<<month<<"\nYear - " << year<<"\nType - " <<type<<endl;
    return 4;
}

bool Vehicle::operator<(const Vehicle &v) const {
    if (year==v.year){
        if (month<v.month) return true;
    }else if(year<v.year) return true;
    else return false;
}

float MotorVehicle::calculateTax() const {
    if (year>1995){
        if (fuel=="gas"){
            if (cylinder<=1000) return 14.56;
            else if (cylinder>1000 &&cylinder<=1300) return 29.06;
            else if (cylinder>1300 &&cylinder<=1750) return 45.15;
            else if (cylinder>1750 &&cylinder<=2600) return 113.98;
            else if (cylinder>2600 &&cylinder<=3500) return 181.17;
            else return 320.89;
        }
        else{
            if (cylinder<=1500) return 14.56;
            else if (cylinder>1500 &&cylinder<=2000) return 29.06;
            else if (cylinder>2000 &&cylinder<=3000) return 45.15;
            else return 113.98;
        }
    }
    else{
        if (fuel=="gas"){
            if (cylinder<=1000) return 8.10;
            else if (cylinder>1000 &&cylinder<=1300) return 14.56;
            else if (cylinder>1300 &&cylinder<=1750) return 22.65;
            else if (cylinder>1750 &&cylinder<=2600) return 54.89;
            else if (cylinder>2600 &&cylinder<=3500) return 87.13;
            else return 148.37;
        }
        else{
            if (cylinder<=1500) return 8.10;
            else if (cylinder>1500 &&cylinder<=2000) return 14.56;
            else if (cylinder>2000 &&cylinder<=3000) return 22.65;
            else return 54.89;
        }
    }
}

float Bicycle::calculateTax() const{
    return 0;
}