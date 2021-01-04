#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
using namespace std;

Client::Client() {
    numGifts=rand() % 5 + 1;
}

unsigned Client::getNumGifts() const {
    return numGifts;
}

Counter::Counter(unsigned wt): wrappingTime(wt) {
    actualTime=0;
    nextEnter=rand() % 20 + 1;
    nextLeave=0;
    numAttendedClients=0;
}

unsigned Counter::getActualTime() const {
    return actualTime;
}

unsigned Counter::getNextEnter() const {
    return nextEnter;
}

unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}

unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}

unsigned Counter::getNextLeave() const {
    return nextLeave;
}

Client & Counter::getNextClient() {
    if (clients.empty()) throw EmptyQueue();
    else {
        return clients.front();
    }
}

void Counter::enter()
{
    clients.push(Client());
    if (clients.size()==1)nextLeave=actualTime+clients.front().getNumGifts()*wrappingTime;
    nextEnter=rand() % 20 + 1+actualTime;
    cout << "Enter - Actual Time: " << actualTime << " , Num of gift: " << clients.back().getNumGifts()<<endl;

}

void Counter::leave()
{
    getNextClient();
    cout << "Leave - Actual Time: " << actualTime << " , Num of gift: " << clients.front().getNumGifts()<<endl;
    clients.pop();
    nextLeave=actualTime+clients.front().getNumGifts()*wrappingTime;
    numAttendedClients++;
}


void Counter:: nextEvent()
{
    if (clients.empty()){actualTime=nextEnter;enter();}
    else if (nextLeave<nextEnter){actualTime=nextLeave;leave();}
    else if (nextLeave==nextEnter){actualTime=nextLeave;leave();enter();}
    else{actualTime=nextEnter;enter();}
}


//TODO
ostream & operator << (ostream & out, const Counter & c2)
{
    out<<"Attended clients: "<<c2.getNumAttendedClients()<< " , Missing clients: "<< c2.clients.size()<<endl;
    return out;
}


