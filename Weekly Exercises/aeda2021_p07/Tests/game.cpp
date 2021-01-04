#include "game.h"
#include <sstream>

BinaryTree<Circle> getLeft(unsigned int p,vector<int> &points, vector<bool> &states);
BinaryTree<Circle> getRight(unsigned int p,vector<int> &points, vector<bool> &states);

//TODO
ostream &operator << (ostream &os, Circle &c1)
{
	return os;
}

BinaryTree<Circle> getRight(unsigned int p,vector<int> &points, vector<bool> &states){
    if (2*p+2>points.size()-1){
        return BinaryTree<Circle>(Circle(points[p],states[p]));
    }
    else return BinaryTree<Circle>(Circle(points[p],states[p]),getLeft(2*p+1,points,states),getRight(2*p+2,points,states));
}

BinaryTree<Circle> getLeft(unsigned int p,vector<int> &points, vector<bool> &states){
    if (2*p+1>points.size()-1){
        return BinaryTree<Circle>(Circle(points[p],states[p]));
    }
    else return BinaryTree<Circle>(Circle(points[p],states[p]),getLeft(2*p+1,points,states),getRight(2*p+2,points,states));
}

//TODO
Game::Game(int h, vector<int> &points, vector<bool> &states)
{
    if (points.size()>0)
        game = BinaryTree<Circle>(Circle(points[0],states[0]),getLeft(1,points,states),getRight(2,points,states));
}


//TODO
string Game::writeGame()
{
    string res;
    BTItrLevel<Circle> iter=BTItrLevel<Circle>(game);
    while (!iter.isAtEnd()){
        res+=to_string(iter.retrieve().getPoints())+ "-";
        if (iter.retrieve().getState()) res+="true-"+ to_string(iter.retrieve().getNVisits())+"\n";
        else res+="false-"+to_string(iter.retrieve().getNVisits())+"\n";
        iter.advance();
    }
	return res;
}


//TODO
int Game::move()
{
    int res;
    unsigned  int actualP=0,moveP=0;
    BTItrLevel<Circle> iter=BTItrLevel<Circle>(game);
    while (!iter.isAtEnd()){
        if (iter.retrieve().getState()) moveP=actualP*2+2;
        else moveP=actualP*2+1;
        res=iter.retrieve().getPoints();
        iter.retrieve().changeState();
        iter.retrieve().incrementVisits();
        for (int i = actualP; i < moveP ; ++i) {
            if (!iter.isAtEnd()) iter.advance();
            else break;
        }
        actualP=moveP;
    }
	return res;
}


//TODO
int Game::mostVisited()
{
    int res=0;
    BTItrLevel<Circle> iter=BTItrLevel<Circle>(game);
    if (!iter.isAtEnd())
        iter.advance();
    while (!iter.isAtEnd()){
        if (iter.retrieve().getNVisits()>res)
            res=iter.retrieve().getNVisits();
        iter.advance();
    }
    return res;
}
