#include "Warehouse.h"
#include <algorithm>

Warehouse::Warehouse()  {
}

queue<ThinTallBox> Warehouse::getBoxes() {
	return boxes;
}

queue<Object> Warehouse::getObjects() {
    return objects;
}

void Warehouse::setBoxes(queue<ThinTallBox> q) {
    while (!q.empty()) {
        boxes.push(q.front());
        q.pop();
    }
}

void Warehouse::addObject(Object o1) {
    objects.push(o1);
}


int Warehouse::InsertObjectsInQueue(vector <Object> obj){
    sort(obj.begin(), obj.end());
    for(Object object:obj){
        addObject(object);
    }
    return obj.size();
}

Object Warehouse::RemoveObjectQueue(int maxSize){
    vector<Object> new_objects;
    while(!objects.empty()) {
        new_objects.push_back(objects.front());
        objects.pop();
    }
    auto it=new_objects.begin();
    for (auto iter = it; iter != new_objects.end() ; ++iter) {
        if (iter->getSize()<=maxSize){it=iter; break;}
    }
    if (it==new_objects.begin()){
        for (Object obj:new_objects) {
            objects.push(obj);
        }
        return Object("dummy",maxSize);
    }
    else{
        Object res=*it;
        new_objects.erase(it);
        for (Object obj:new_objects) {
            objects.push(obj);
        }
        return res;
    }
}

int Warehouse::addPackOfBoxes(vector <ThinTallBox> boV) {
    for(ThinTallBox box:boV){
        boxes.push(box);
    }
    return boxes.size();
}

void Warehouse::processBox(ThinTallBox &ttb) {
    vector<Object> objects_vect;
    Object dummy("dummy",0);
    double initial_content=ttb.getContentSize();
    while (!objects.empty()){
        if (objects.front().getSize()+initial_content<=ttb.getCapacity()){
            dummy=objects.front(); objects.pop(); break;
        }
        objects_vect.push_back(objects.front());
        objects.pop();
    }
    while (!objects.empty()){
        objects_vect.push_back(objects.front());
        objects.pop();
    }
    for (Object obj:objects_vect) {objects.push(obj);}
    ttb.insert(dummy);
}

vector<ThinTallBox> Warehouse::DailyProcessBoxes(){
    vector<ThinTallBox> res;
    vector<ThinTallBox> remain;
    while (!boxes.empty()){
        ThinTallBox ttb=boxes.front();
        if (ttb.getContentSize()==ttb.getCapacity()){ //Caixa cheia
            res.push_back(boxes.front());
        }
        else if(ttb.getDays()==0){//Expired date
            processBox(ttb);
            res.push_back(ttb);
        }
        else{
            processBox(ttb);
            ttb.setDaysToSend(ttb.getDays()-1);
            remain.push_back(ttb);
        }
        boxes.pop();
    }
    addPackOfBoxes(remain);
    return res;
}

