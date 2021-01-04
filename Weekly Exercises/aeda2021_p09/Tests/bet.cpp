#include "bet.h"
#include <iostream>
#include <sstream>
using namespace std;


//TODO
bool Bet::contains(unsigned num) const
{
	return !(numbers.find(num)==numbers.end());
}

//TODO
void Bet::generateBet(const vector<unsigned>& values, unsigned n)
{
    for (int i = 0; i < values.size(); ++i) {
        if (n==0) break;
        else{
            if(numbers.insert(values[i]).second){
                n--;
            }
        }
    }
}

//TODO
unsigned Bet::countRights(const tabHInt& draw) const
{
    unsigned res=0;
    for (unsigned x:draw) {
        if (contains(x))
            res++;
    }
	return res;
}
