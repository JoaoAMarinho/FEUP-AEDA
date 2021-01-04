#include "fleet.h"
#include <string>

using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}

void Fleet::addVehicle(Vehicle *v1){
    vehicles.push_back(v1);
}

int Fleet::numVehicles() const{
    return vehicles.size();
}

int Fleet::lowestYear() const{
    if (vehicles.size()==0) return 0;
    else{
        int lowestYear=INT_MAX;
        for (auto iter = vehicles.begin(); iter != vehicles.end() ; ++iter) {
            if ((*iter)->getYear()<lowestYear)
                lowestYear=(*iter)->getYear();
        }
        return lowestYear;
    }
}

ostream &operator<<(ostream &o, const Fleet &f) {
    for (auto iter=f.vehicles.begin(); iter!=f.vehicles.end() ; ++iter) {
        (*iter)->info();
    }
    return o;
}

vector<Vehicle *> Fleet::operator()(int yearM) const {
    vector<Vehicle *> v;
    for (auto iter=vehicles.begin(); iter!=vehicles.end() ; ++iter) {
        if ((*iter)->getYear()==yearM) v.push_back(*iter);
    }
    return v;
}

float Fleet::totalTax() const{
    float totalTax;
    for (auto iter=vehicles.begin(); iter!=vehicles.end() ; ++iter) {
        totalTax+=(*iter)->calculateTax();
    }
    return totalTax;
}

unsigned Fleet::removeOldVehicles(int y1){
    unsigned n=0;
    for (auto iter=vehicles.begin(); iter!=vehicles.end() ; ++iter) {
        if ((*iter)->getYear()<=y1){
            vehicles.erase(iter);
            --iter;
            ++n;
        }
    }
    return n;
}