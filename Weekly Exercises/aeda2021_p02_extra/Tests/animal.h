#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinary.h"
#include <string>
#include<sstream>
using namespace std;

class Animal {
protected:
    string name;
    int age;
    Veterinary *vet;
    static int youngest;
public:
    /**
     * Class Animal constructor
     * @param name - Animal name
     * @param age - Animal age
     */
    Animal(string name, int age);
    /**
     * Class Animal destructor
     */
    virtual ~Animal(){};
    /**
     *
     * @return Class member name
     */
    string getName() const;
    /**
     *
     * @return Class member age
     */
    int getAge() const;
    /**
     *
     * @return Pointer to the current animal veterinary
     */
    Veterinary *getVeterinary() const;
    /**
     * Changes the current veterinary to the param vet
     * @param vet - pointer to the new vet
     */
    void setVeterinary(Veterinary *vet);
    /**
     *
     * @return the static member youngest
     */
    static int getYoungest();
    /**
     * Virtual function, other functions might be called depending on the specific sub-class
     * @return string with info concerning the name, age, name of the veterinary (if any)
     */
    virtual string getInfo() const;
    /**
     * Function to know if an Animal is considered young
     * @return always false
     */
    virtual bool isYoung() const = 0;
};

class Dog: public Animal {
    string breed;
public:
    /**
     * Class Dog constructor
     * @param name - Dog name
     * @param age - Dog age
     * @param breed - Dog breed
     */
   Dog(string name, int age, string breed);
   /**
    *
    * @return string with info concerning the name, age, name of the veterinary (if any) and breed
    */
   string getInfo() const;
   /**
    * If age<5 - false, else - true
    * @return the boolean value related to the Dog's youth
    */
   bool isYoung ()const;
};


class Flying {
    int maxVelocity;
    int maxAltitude;
public:
    /**
     * Class Flying constructor
     * @param maxv - Animal Flying max Velocity
     * @param maxa - Animal Flying max Altitude
     */
   Flying(int maxv, int maxa);
   /**
    *
    * @return  Class member maxVelocity
    */
   int getmaxV() const;
   /**
    *
    * @return Class member maxAltitude
    */
   int getmaxA() const;
//to complete
};


class Bat: public Animal, public Flying {
public:
    /**
     * Class Bat constructor
     * @param name - Bat name
     * @param age - Bat age
     * @param maxv - Bat max Velocity
     * @param maxa - Bat max Altitude
     */
    Bat(string name, int age, int maxv, int maxa);
    /**
     * If age<4 - false, else - true
     * @return string with info concerning the name, age, name of the veterinary (if any), max Velocity and max Altitude
     */
    string getInfo() const;
    /**
     *
     * @return the boolean value related to the Bat's youth
     */
    bool isYoung ()const;
};

#endif /* SRC_ANIMAL_H_ */
