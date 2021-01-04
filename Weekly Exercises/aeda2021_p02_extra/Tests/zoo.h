#ifndef ZOO_H_
#define ZOO_H_

#include "animal.h"
#include <vector>

class Zoo {
	vector<Animal *> animals;
	vector<Veterinary *> veterinarians;
public:
    /**
     *
     * @return size of vector animals
     */
	unsigned numAnimals() const;
	/**
	 *
	 * @return size of vector veterinarians
	 */
	unsigned numVeterinarians() const;
	/**
	 * Adds a pointer, to an Animal, to the vector animals
	 * @param a1 - Pointer to Class Animal
	 */
    void addAnimal(Animal *a1);
    /**
     *
     * @return string with all the info about the Animals in the vector animals
     */
    string getInfo() const;
    /**
     *
     * @param nameA - name of the Animal to be searched
     * @return the boolean value related to the Animal, with the name nameA, youth
     */
    bool isYoung(string nameA);
    /**
     * Function that reads information about the veterinaries and distributes them to the respective Animal, belonging to the vector animals
     * @param isV - reference to a file with the information on the veterinaries
     */
    void allocateVeterinarians(istream &isV);
    /**
     * Function that searches for the vet with nameV, breaks the link with the Animal if possible and removes the vet from the vector veterinarians
     * @param nameV - name of the veterinary to be removed from the vector veterinarians
     * @return the boolean value to whether it's possible to remove the vet with nameV or not
     */
    bool removeVeterinary(string nameV);
    /**
     * Function that compares the sum of all the Animal ages between the two Zoo's
     * @param zoo2 - Class Zoo to be compared
     * @return boolean value to whether the first Zoo is lower than the parameter
     */
    bool operator < (Zoo& zoo2) const;
};


#endif /* ZOO_H_ */
