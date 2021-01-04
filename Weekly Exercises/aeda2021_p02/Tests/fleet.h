#ifndef FLEET_H_
#define FLEET_H_

#include <vector>
#include "vehicle.h"
using namespace std;

class Fleet {
	vector<Vehicle *> vehicles;
public:
    void addVehicle(Vehicle *v1);
    vector<Vehicle *> getVehicles() const;
    vector<Vehicle *> operator () (int yearM) const;
	friend ostream & operator<<(ostream & o, const Fleet & f);
    unsigned removeOldVehicles(int y1);
    float totalTax() const;
    int numVehicles() const;  // retorna o nº de veículos no vector veiculos
    int lowestYear() const;   // retorna o menor ano dos veículos presentes no vetor veículos
                              // retorna 0 se não existir nenhum veículo

};




#endif /*FLEET_H_*/
