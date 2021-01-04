#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

// TODO Y
Game::Game()=default;

// TODO Y
Game::Game(list<Kid>& l2)
{
    for (auto it = l2.begin(); it != l2.end() ; ++it) {
        kids.push_back(*it);
    }
}

// TODO Y
void Game::addKid(const Kid &k1)
{
    kids.push_back(k1);
}

// TODO Y
list<Kid> Game::getKids() const
{
    return kids;
}

// TODO Y
string Game::write() const
{
    string res;
    for (auto it = kids.begin(); it != kids.end() ; ++it) {
        res+=it->write()+"\n";
    }
    return res;
}

// TODO Y
Kid& Game::loseGame(string phrase)
{
    auto it=kids.begin();
    it=kids.begin();
    unsigned int lenght= numberOfWords(phrase);
    while(kids.size()!=1){
        unsigned int size = lenght-1;
        while (size!=0){
            ++it;
            if (it==kids.end()) it=kids.begin();
            size--;
        }
        it = kids.erase(it);
        if(it==kids.end()) it=kids.begin();
    }
    return kids.front();
}

// TODO Y
list<Kid>& Game::reverse()
{
    kids.reverse();
    return kids;
}

// TODO Y
list<Kid> Game::removeOlder(unsigned id)
{
    list<Kid> res;
    for (auto it = kids.begin(); it != kids.end() ; ++it) {
        if (it->getAge()>id) res.push_back(*it);
    }
    return res;
}

// TODO Y
void Game::setKids(const list<Kid>& l1)
{
    kids = l1;
}

// TODO Y
bool Game::operator==(Game& g2)
{
    if (kids.size()!=g2.kids.size()) return false;
    else{
        auto it1=kids.begin();
        auto it2=g2.kids.begin();
        for (int i = 0; i < g2.kids.size(); ++i) {
            if ((*it1)==(*it2)) {++it1;++it2;}
            else return false;
        }
        return true;
    }
}

// TODO Y
list<Kid> Game::shuffle() const
{
    list<Kid> res;
    vector<Kid> vec;
    for (auto it = kids.begin(); it != kids.end() ; ++it) {
        vec.push_back(*it);
    }
    random_shuffle(vec.begin(),vec.end());
    for (auto it = vec.begin(); it != vec.end() ; ++it) {
        res.push_back(*it);
    }
    return res;
}
