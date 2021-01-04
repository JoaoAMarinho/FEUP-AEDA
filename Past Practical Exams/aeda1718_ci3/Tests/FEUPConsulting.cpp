/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
	//TODO
	auto iter=BSTItrIn<Expertize>(expertizes);
	bool found=false;
	while (!iter.isAtEnd()){
	    if(iter.retrieve().getName()==expertizeAvailable && iter.retrieve().getCost()==cost){
	        iter.retrieve().addConsultant(student);
	        found=true;
            break;
	    }
	    iter.advance();
	}
	if (!found){
	    Expertize x=Expertize(expertizeAvailable,cost);
	    x.addConsultant(student);
	    expertizes.insert(x);
	}
}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	//TODO:
    auto iter=BSTItrIn<Expertize>(expertizes);
    bool found=false;
    while (!iter.isAtEnd()){
        if(iter.retrieve().getName()==project->getExpertize() && iter.retrieve().getCost()==project->getCost()){
            for(Student* student:iter.retrieve().getConsultants()){
                if(student->getCurrentProject()==""){
                    temp.push_back(student);
                }
            }
            break;
        }
        iter.advance();
    }
	return temp;
}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
	//TODO:
    if(project->getConsultant()!=NULL){return false;}
    else{
        vector<Student*> students=getCandidateStudents(project);
        for(Student* st:students){
           if(st->getName()==student->getName() && st->getEMail()==student->getEMail()){
               project->setConsultant(student);
               student->addProject(project->getTitle());
               return true;
           }
        }
        return false;
    }
}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
	//TODO:
    students.insert(student);
}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	//TODO
	auto iter=students.begin();
	while (iter!=students.end()){
	    if(iter->getEMail()==student->getEMail()){
	        iter=students.erase(iter);
	        students.insert(new Student(student->getName(),newEMail));
	    }
	    else iter++;
	}
}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	//TODO:
	for(Student st:candidates){
	    if(st.getPastProjects().size()>=min){
	        activeStudents.push(st);
	    }
	}
}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
	//TODO:
    if(activeStudents.empty()) return 0;
	int max;
	int current_max=0;
	Student sto("","");
	priority_queue<Student> vect(activeStudents);
	while(!vect.empty()){
        max=vect.top().getPastProjects().size();
        if(max==current_max){
            return 0;
        }else if(max<current_max){
            break;
        }
	    if(current_max==0){
	        current_max=max;
	        sto=vect.top();
	    }
	    vect.pop();
	}
	studentMaximus=sto;
	return activeStudents.size();

}





















