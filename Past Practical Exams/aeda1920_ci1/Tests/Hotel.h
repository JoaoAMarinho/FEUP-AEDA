#ifndef SRC_HOTEL_H_
#define SRC_HOTEL_H_

#include <vector>
#include <list>

template <class Chamber>
class Hotel {
	std::vector<Chamber *> chambers;
	const unsigned int maxCapacity;
	const std::string city;
    std::list<Chamber> reservationsDone;
public:
	Hotel(int size, std::string municipality);
	~Hotel();
	std::vector<Chamber *> getChambers() const;
	void setChambers(std::vector<Chamber *> chambers);
	int getCapacity() const;
    std::list<Chamber> getReservationsDone() const;
	bool addChamber(Chamber *chamber);
    void addReservationDone(Chamber chamber);
    Chamber* removeChamber(std::string code, int floor);
	float avgArea(int floor) const;
	void sortChambers();
	bool doReservation(std::string code, int floor);
    std::list<Chamber> roomsNeverReserved() const;
};

//TODO
class NoSuchFloorException {
private:
    int floor;
public:
    NoSuchFloorException(int floor):floor(floor){}
    int getFloor() { return floor;}
};

class NoSuchChamberException {
public:
	NoSuchChamberException() { }
};

template <class Chamber>
Hotel<Chamber>::Hotel(int size, std::string municipality) : maxCapacity(size), city(municipality) {
}

template <class Chamber>
Hotel<Chamber>::~Hotel(){
	typename std::vector<Chamber *>::const_iterator it;
	for (it=chambers.begin(); it!=chambers.end(); it++) {
		delete *it;
	}
}

template<class Chamber>
std::vector<Chamber *> Hotel<Chamber>::getChambers() const {
	return chambers;
}

template<class Chamber>
void Hotel<Chamber>::setChambers(std::vector<Chamber*> chambers) {
	this->chambers = chambers;
}

template<class Chamber>
int Hotel<Chamber>::getCapacity() const {
	return maxCapacity;
}

template<class Chamber>
void Hotel<Chamber>::addReservationDone(Chamber chamber) {
    reservationsDone.push_back(chamber);
}

template<class Chamber>
std::list<Chamber> Hotel<Chamber>::getReservationsDone() const {
    return reservationsDone;
}

//------------------------------------------------------
//------------------------------------------------------

//TODO
template<class Chamber>
bool Hotel<Chamber>::addChamber(Chamber *chamber) {
    for (Chamber* ch: chambers) {
        if(*ch==*chamber) return false;
    }
    if(chambers.size()+1<=maxCapacity){
        chambers.push_back(chamber); return true;
    }
    else return false;
}

template<class Chamber>
bool Comparator(Chamber* ch1,Chamber* ch2){
    if(ch1->getCode()==ch2->getCode()) return ch1->getFloor()>ch2->getFloor();
    else return ch1->getCode()<ch2->getCode();
}


//TODO
template<class Chamber>
void Hotel<Chamber>::sortChambers() {
    sort(chambers.begin(),chambers.end(),Comparator<Chamber>);
}

//TODO
template<class Chamber>
Chamber* Hotel<Chamber>::removeChamber(std::string code, int floor) {
    for (int i = 0; i < chambers.size(); ++i) {
        if (*chambers[i]==Chamber(code,floor)){ auto value=chambers[i];chambers.erase(chambers.begin()+i);return value;};
    }
    throw NoSuchChamberException();
}

//TODO
template<class Chamber>
float Hotel<Chamber>::avgArea(int floor) const {
    float  avg=0.0;
    int counter=0;
    for (Chamber* ch:chambers) {
        if (ch->getFloor()==floor) {counter++;avg+=ch->getArea();}
    }
    if (counter!=0) return avg/counter;
    else throw NoSuchFloorException(floor);
}

//TODO
template<class Chamber>
bool Hotel<Chamber>::doReservation(std::string code, int floor){
    for (Chamber* ch:chambers) {
        if (*ch==*new Chamber(code,floor) && !ch->getReservation()){ch->setReservation(true);reservationsDone.push_back(*ch);return true; }
    }
    return false;
}

//TODO
template<class Chamber>
std::list<Chamber> Hotel<Chamber>::roomsNeverReserved() const {
    std::list<Chamber> res;
    bool in=false;
    for (Chamber* ch:chambers) {
        for (auto reserved = reservationsDone.begin();reserved!=reservationsDone.end() ; ++reserved) {
            if (*ch==*reserved){in=true; break;}
        }
        if (!in) res.push_back(*ch);
        in=false;
    }
    return res;
}



#endif /* SRC_HOTEL_H_ */
