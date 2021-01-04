/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {
	//TODO:
	vector<BookCatalogItem> vect;
	bool found;
	for(Book* book:books){
        found=false;
	    for(BookCatalogItem &bci:vect){
	        if(bci==BookCatalogItem(book->getTitle(),book->getAuthor(),book->getYear())){
                bci.addItems(book);
                found= true;
                break;
	        }
	    }
	    if(!found){
	        BookCatalogItem x=BookCatalogItem(book->getTitle(),book->getAuthor(),book->getYear());
	        x.addItems(book);
	        vect.push_back(x);
	    }
	}
	for(BookCatalogItem bci:vect){
	    catalogItems.insert(bci);
	}

}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
	//TODO:
	auto iter=BSTItrIn<BookCatalogItem>(catalogItems);
	while (!iter.isAtEnd()){
	    if(iter.retrieve()==BookCatalogItem(book->getTitle(),book->getAuthor(),book->getYear())){
	        for(Book* book:iter.retrieve().getItems()){
	            if(book->getReader()==NULL){
	                temp.push_back(book);
	            }
	        }
	    }
	    iter.advance();
	}
	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	//TODO:
    auto iter=BSTItrIn<BookCatalogItem>(catalogItems);
    while (!iter.isAtEnd()){
        if(iter.retrieve()==BookCatalogItem(book->getTitle(),book->getAuthor(),book->getYear())){
            for(Book* book:iter.retrieve().getItems()){
                if(book->getReader()==NULL){
                    book->setReader(reader);
                    reader->addReading(book->getTitle(),book->getAuthor());
                    return true;
                }
            }
        }
        iter.advance();
    }
    return false;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
	//TODO:
    userRecords.insert(user);
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	//TODO:
	auto iter=userRecords.begin();
	while (iter!=userRecords.end()){
	    if(user->getEMail()==iter->getEMail()){
	        iter=userRecords.erase(iter);
	        user->setEMail(newEMail);
	        userRecords.insert(user);
            break;
	    }
	    iter++;
	}
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	//TODO:
	int number_lectures=0;
	for(User user:candidates){
	    if(user.getReading().first!="") number_lectures++;
	    number_lectures+=user.getReadings().size();
        if(number_lectures>=min) readerCandidates.push(user);
	    number_lectures=0;
	}
}

int ReadingClub::awardReaderChampion(User& champion) {
	//TODO:
	if(readerCandidates.empty()) {
        return 0;
    }
	else if(readerCandidates.size()==1) {champion=readerCandidates.top(); return 1;}
	else{
        priority_queue<User> candidates(readerCandidates);
        int x0=0,x1=0;
        if(candidates.top().getReading().first!="") x0++;
        x0+=candidates.top().getReadings().size();
        candidates.pop();
        if(candidates.top().getReading().first!="") x1++;
        x1+=candidates.top().getReadings().size();
        if(x0==x1) return 0;
        else{
            champion=readerCandidates.top(); return readerCandidates.size();
        }
	}
}
























