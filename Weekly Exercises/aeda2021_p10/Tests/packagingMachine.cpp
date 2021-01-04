#include "packagingMachine.h"
#include <sstream>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap)
{}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}


// TODO
unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
    unsigned  res=0;
    auto object = objs.begin();
    while (object!=objs.end()){
        if (object->getWeight()<=boxCapacity){
            objects.push(*object);
            res++;
            objs.erase(object);
        }
        else{
            object++;
        }
    }
	return res;
}

// TODO
Box PackagingMachine::searchBox(Object& obj) {
	Box b;
	vector<Box> temp;
	while (!boxes.empty()){
        if(boxes.top().getFree()>=obj.getWeight()){b=boxes.top();boxes.pop(); break;}
        else{temp.push_back(boxes.top());boxes.pop();}
    }
    for (Box x:temp) {
        boxes.push(x);
    }
    return b;
}

// TODO
unsigned PackagingMachine::packObjects() {
    Object obj(0,0);
    while (!objects.empty()){
        obj=objects.top();
        Box b=searchBox(obj);
        b.addObject( obj );
        addBox( b );
        objects.pop();
    }
	return boxes.size();
}

// TODO
string PackagingMachine::printObjectsNotPacked() const {
    if (objects.empty())
	    return "No objects!\n";
    string res;
    HeapObj Objects=getObjects();
    while (!Objects.empty()){
        Object obj=Objects.top();
        res+= "O" + to_string(obj.getID()) + ":" + to_string(obj.getWeight()) + "\n";
        Objects.pop();
    }
    return res;
}

// TODO
Box PackagingMachine::boxWithMoreObjects() const {
	if (boxes.empty()) throw MachineWithoutBoxes();
    Box b;
    unsigned maxSize=0;
    HeapBox Boxs=getBoxes();
    while (!Boxs.empty()){
        if (Boxs.top().getSize()>maxSize){
            maxSize=Boxs.top().getSize();
            b=Boxs.top();
        }
        Boxs.pop();
    }
	return b;
}