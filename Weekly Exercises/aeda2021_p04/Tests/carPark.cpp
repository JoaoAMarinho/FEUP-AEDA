#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
using namespace std;

CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli)
{
    freePlaces=cap;
}

vector<InfoCard> CarPark::getClients() const
{
    return clients;
}

unsigned CarPark::getNumPlaces() const
{
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const
{
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const
{
    return numMaxClients;
}

unsigned CarPark::getNumClients() const
{
    return clients.size();
}


int CarPark::clientPosition(const string & name) const
{
    InfoCard x;
    x.name=name;
    return sequentialSearch(clients,x);
}


unsigned CarPark::getFrequency(const string &name) const
{
    int pos = clientPosition(name);
    if (pos == -1) {
        InfoCard x;
        x.name=name;
        throw ClientDoesNotExist(x);
    }
    return clients[pos].frequency;
}

bool InfoCard::operator<(const InfoCard & A) const{
    if(frequency>A.frequency) return true;
    else if(frequency==A.frequency){
        if(name<A.name) return true;
        else return false;
    }
    else return false;
}

bool CarPark::addClient(const string & name)
{
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name=name;
    info.present=false;
    info.frequency=0;
    clients.push_back(info);
    return true;
}

bool CarPark::removeClient(const string & name)
{
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( (*it).present == false ) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}

bool CarPark::enter(const string & name)
{
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == true) return false;
    clients[pos].present = true;
    freePlaces--;
    clients[pos].frequency++;
    return true;
}

bool CarPark::leave(const string & name)
{
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == false) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}

InfoCard CarPark::getClientAtPos(unsigned p) const
{
    InfoCard info;
    if (p<clients.size()) {info=clients[p]; return info;}
    else info.frequency=p; throw PositionDoesNotExist(info);
}

void CarPark::sortClientsByFrequency()
{
    insertionSort(clients);
}

bool cmpNames(const InfoCard &A,const InfoCard &B){return A.name<B.name;}
void CarPark::sortClientsByName()
{
    sort(clients.begin(),clients.end(),cmpNames);
}

vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2)
{
    vector<string> names;
    sortClientsByFrequency();
    for (int i = 0; i < clients.size(); ++i) {
        int freq=clients[i].frequency;
        if (freq>=f1 && freq<=f2) names.push_back(clients[i].name);
    }
    return names;
}


ostream & operator<<(ostream & os, const CarPark & cp)
{
    for (int i = 0; i < cp.clients.size(); ++i) {
        os<<"Client name: "<< cp.clients[i].name <<" / ";
        if (cp.clients[i].present) os<<"Client presence: Present / Client frequency: " << cp.clients[i].frequency<<endl;
        else os<<"Client presence: Not present / Client frequency: " << cp.clients[i].frequency <<endl;
    }
    return os;
}
