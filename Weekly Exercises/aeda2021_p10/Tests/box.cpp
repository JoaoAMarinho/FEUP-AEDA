#include "box.h"
#include <sstream>

Object::Object(unsigned i, unsigned w): id(i), weight(w)
{}

unsigned Object::getID() const {
    return id;
}

unsigned Object::getWeight() const {
    return weight;
}

Box::Box(unsigned cap): id(lastId++), capacity(cap), free(cap)
{}

unsigned Box::getID() const {
    return id;
}

unsigned Box::getFree() const {
    return free;
}

StackObj Box::getObjects() const {
    return objects;
}

void Box::addObject(Object& obj) {
    free -= obj.getWeight();
    objects.push(obj);
}

void Box::resetID(){
    lastId = 1;
}

unsigned Box::getSize() const {
    return objects.size();
}


ostream& operator<<(ostream& os, Object obj) {
    os << "O" << obj.id << ":" << obj.weight;
    return os;
}

unsigned Box::lastId = 1;


// TODO
bool Object::operator<(const Object& o1) const {
	return weight<o1.getWeight();
}

// TODO
bool Box::operator<(const Box& b1) const {
	return free>b1.getFree();
}

// TODO
string Box::printContent() const {
    if (objects.empty()) return "Box "+to_string(id) +" empty!\n";
	string res="Box "+to_string(id) +" [ ";
	StackObj Objects=getObjects();
	while (!Objects.empty()){
	    res+="O" + to_string(Objects.top().getID()) + ":" + to_string(Objects.top().getWeight()) +" ";
	    Objects.pop();
	}
	res += "]";
    return res;
}

