#include "Gallery.h"
#include <ostream>
using namespace std;

Gallery::Gallery(vector<Paint*> c): catalog(PaintCatalogItem("", "", 0, 0.00)), collection(c) {

}

vector<Paint*> Gallery::getCollection() const {
    return collection;
}

void Gallery::setCollection(vector<Paint*> c) {
    collection = c;
}

priority_queue<ExhibitionItem> Gallery::getPaintsToShow() const {
    return paintsToShow;
}
HashTableAuthorRecord Gallery::getAuthorRecords () const {
    return  authorRecords;
}

void Gallery::addAuthorRecord(AuthorRecord ar) {
    authorRecords.insert(ar);
}

void Gallery::generateCatalog() {
    catalog.makeEmpty();
    for(int i = 0; i < collection.size(); i++) {
        catalog.insert(collection[i]);
    }
}

BST<PaintCatalogItem> Gallery::getCatalog() const {
    return catalog;
}


void Gallery::prepareExhibition() {
    while( !paintsToShow.empty())
        paintsToShow.pop();
    for(int i = 0; i < collection.size(); i++) {
        ExhibitionItem ei(collection[i]);
        paintsToShow.push(ei);
    }
}

//-------------------------------------------------------------------------------

//TODO
vector<Paint*> Gallery::getPaintsBy(string a) const {
    vector<Paint*> tmp;
    auto iter=BSTItrIn<PaintCatalogItem>(catalog);
    while (!iter.isAtEnd()){
        PaintCatalogItem paintPointer=iter.retrieve();
        if(paintPointer.getAuthor()==a){
            tmp.push_back(paintPointer.getPaint());
        }
        iter.advance();
    }
    return tmp;
}

//TODO
vector<Paint*> Gallery::getPaintsBetween(int y1, int y2) const {
    vector<Paint*> tmp;
    auto iter=BSTItrIn<PaintCatalogItem>(catalog);
    while (!iter.isAtEnd()){
        PaintCatalogItem paintPointer=iter.retrieve();
        if(paintPointer.getYear()>=y1 && paintPointer.getYear()<=y2){
            tmp.push_back(paintPointer.getPaint());
        }
        iter.advance();
    }
    return tmp;
}

//TODO
bool Gallery::updateTitle(Paint* p, string tnew) {
    auto iter=BSTItrIn<PaintCatalogItem>(catalog);
    while (!iter.isAtEnd()){
        PaintCatalogItem paintPointer=iter.retrieve();
        if(paintPointer.getAuthor()==p->getAuthor() && paintPointer.getTitle()==p->getTitle()){
            paintPointer.setTitle(tnew);
            return true;
        }
        iter.advance();
    }
    return false;
}


//TODO
int Gallery::recordAvailablePainters() { //carrega a tabela de dispersao com AuthorRecords
    for(Paint* paint:collection){
        auto iter=authorRecords.find(AuthorRecord(paint->getAuthor()));
        if(iter==authorRecords.end()){
            authorRecords.insert(AuthorRecord(paint->getAuthor(),1,0));
        }
        else{
            auto a=AuthorRecord(iter->getAuthor(),iter->getAvailablePaints()+1,0);
            authorRecords.erase(iter);
            authorRecords.insert(a);
        }
    }
    return authorRecords.size();
}

//TODO
double Gallery::totalSells() const {
    double res=0;
    for (auto iter=authorRecords.begin(); iter != authorRecords.end();iter++) {
        res+=iter->getTotalSells();
    }
    return res;
}

//TODO
double Gallery::sellPaint(string a, string t) {
    double res=0.0;
    for (auto paint=collection.begin(); paint!=collection.end(); paint++) {
        if ((*paint)->getTitle()==t){
            res=(*paint)->getPrice();
            collection.erase(paint);
            break;
        }
    }
    if(res!=0){
        auto iter=authorRecords.find(AuthorRecord(a));
        auto autor=AuthorRecord(iter->getAuthor(),iter->getAvailablePaints()-1,iter->getTotalSells()+res);
        authorRecords.erase(iter);
        authorRecords.insert(autor);
    }
    return res;
}

//TODO
vector<Paint*> Gallery::nBestExibition(int n, int maxPerYear) {  //escolhe as N mais caras pinturas, dos anos mais antigos, para realizar uma exposição
    vector<Paint*> tmp;
    vector<ExhibitionItem> vect;
    int actualyear, maxnperyear=maxPerYear;
    while (!paintsToShow.empty()){
        if (n!=0){
            actualyear=paintsToShow.top().getYear();
            if (!tmp.empty() && actualyear==tmp.back()->getYear()){
                maxnperyear--;
                if (maxnperyear>0){
                    tmp.push_back(paintsToShow.top().getPaint());
                    paintsToShow.pop();
                    n--;
                }else {
                    vect.push_back(paintsToShow.top());
                    paintsToShow.pop();
                }
            }
            else{
                maxnperyear=maxPerYear;
                tmp.push_back(paintsToShow.top().getPaint());
                paintsToShow.pop();
                n--;
            }
        }else break;
    }
    for(ExhibitionItem exhibitionItem:vect){
        paintsToShow.push(exhibitionItem);
    }
    return tmp;
}

//TODO
int Gallery::itemExibitionOrder(string a, string t) {
    int res=1;
    vector<ExhibitionItem> vect;
    bool found=false;
    while (!paintsToShow.empty()){
        if(paintsToShow.top().getAuthor()==a && paintsToShow.top().getTitle()==t)
        {
            found=true;
            break;
        }else{
            vect.push_back(paintsToShow.top());
            paintsToShow.pop();
            res++;
        }
    }
    for(ExhibitionItem exhibitionItem:vect){
        paintsToShow.push(exhibitionItem);
    }
    if (found){
        return res;
    }
    return 0;
}

