#include "REAgency.h"

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//
void REAgency::generateCatalog() {
	//TODO: A
	vector<PropertyTypeItem> vect;
    for (Property* propertie:properties) {
        if(vect.empty()){
            vect.push_back(PropertyTypeItem(propertie->getAddress(),propertie->getPostalCode(),propertie->getTypology(),propertie->getPrice()));
            vect[0].addItems(propertie);
        }
        else{
            auto x=find(vect.begin(),vect.end(),PropertyTypeItem(propertie->getAddress(),propertie->getPostalCode(),propertie->getTypology(),propertie->getPrice()));
            if(x!=vect.end()){
                x->addItems(propertie);
                if(propertie->getPrice()>x->getMaxPrice()) x->setMaxPrice(propertie->getPrice());
            }
            else{
                vect.push_back(PropertyTypeItem(propertie->getAddress(),propertie->getPostalCode(),propertie->getTypology(),propertie->getPrice()));
                vect.back().addItems(propertie);
            }
        }
    }
    for(PropertyTypeItem pr:vect){
        catalogItems.insert((pr));
    }
}

vector<Property*> REAgency::getAvailableProperties(Property* property) const {
	vector<Property*> temp;
	auto iter=BSTItrIn<PropertyTypeItem>(catalogItems);
	while (!iter.isAtEnd()){
	    if(iter.retrieve().getAddress()==property->getAddress() && iter.retrieve().getPostalCode()==property->getPostalCode() && iter.retrieve().getTypology()==property->getTypology()){
	        auto v=iter.retrieve().getItems();
	        for(Property* pr:v){
	            if(get<0>(pr->getReservation())==NULL){
	                temp.push_back(pr);
	            }
	        }
	    }
	    iter.advance();
	}

	return temp;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {
    auto iter=BSTItrIn<PropertyTypeItem>(catalogItems);
    while (!iter.isAtEnd()){
        if(iter.retrieve().getAddress()==property->getAddress() && iter.retrieve().getPostalCode()==property->getPostalCode() && iter.retrieve().getTypology()==property->getTypology()){
            auto v=iter.retrieve().getItems();
            for(Property* &pr:v){
                if(get<0>(pr->getReservation())==NULL){
                    pr->setReservation(make_tuple(client,pr->getPrice()-pr->getPrice()*percentage/100));
                    client->addVisiting(pr->getAddress(),pr->getPostalCode(),pr->getPostalCode(),to_string(pr->getPrice()));
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
void REAgency::addClientRecord(Client* client) {
	//TODO: D
    listingRecords.insert(client);
}

void REAgency::deleteClients() {
	//TODO: E
	auto iter=listingRecords.begin();
    while (iter!=listingRecords.end()){
        if(iter->getClientPointer()->getVisitedProperties().empty()){
            iter=listingRecords.erase(iter);
        }else{
            iter++;
        }
    }
}

//
// TODO: Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
	//TODO: F
	int reservs=0, nvisits=0;
	for(Client client:candidates){
        nvisits=client.getVisitedProperties().size();
        for(Property* pr:properties){
            if(get<0>(pr->getReservation())->getEMail()==client.getEMail()){
                reservs++;
            }
        }
        if(reservs/(double)nvisits>(double)min)
            clientProfiles.push(client);
        reservs=0;
        nvisits=0;
	}
}

vector<Property*> REAgency::suggestProperties() {
	//TODO: G
	vector<Property*> tempProperties;
	priority_queue<Client> v=clientProfiles;
	int biggest_diff=INT16_MAX;
	int diff=0;
    while (!v.empty()){
        if(get<0>(v.top().getVisiting())!=""){
            Property* pp;
            for(Property* pr:properties){
                if(get<0>(pr->getReservation())==NULL){
                    diff=abs(stoi(get<1>(v.top().getVisiting()))-stoi(pr->getPostalCode()));
                    if(diff<biggest_diff){
                        biggest_diff=diff;
                        pp=pr;
                    }
                }
            }
            tempProperties.push_back(pp);
        }
        v.pop();
    }
	return tempProperties;
}
