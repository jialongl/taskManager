/* Author: He Haocong */

#include "Comparer.h"

Comparer::Comparer(vector<sortKeyword_e> keys){
  isNull = false;
//  keywords = vector<sortKeyword_e>();
  keywords.clear();
  for (int i=0;i<keys.size();i++){
    keywords.push_back(keys[i]);
  }
}

Comparer::Comparer(){
  isNull = true;
//  keywords = new vector<sortKeyword_e>;
  keywords.clear();
  keywords.push_back(SERIAL_NUMBER);
}

Comparer::~Comparer(){
  //delete keywords;
}

int Comparer::compareWithKeyword(Task* task1, Task* task2, sortKeyword_e sk){
  switch (sk){
  case DEADLINE:
    if (task1->getDeadline() < task2->getDeadline()) return -1;
    if (task1->getDeadline() == task2->getDeadline()) return 0;
    if (task1->getDeadline() > task2->getDeadline()) return 1;
    break;
  case PRIORITY:
    if (task1->getPriority() > task2->getPriority()) return -1;
    if (task1->getPriority() == task2->getPriority()) return 0;
    if (task1->getPriority() < task2->getPriority()) return 1;
    break;
  case SERIAL_NUMBER:	
    if (task1->getSerialNumber() < task2->getSerialNumber()) return -1;
    if (task1->getSerialNumber() == task2->getSerialNumber()) return 0;
    if (task1->getSerialNumber() > task2->getSerialNumber()) return 1;
    break;
  }
  return 0;
}

bool Comparer::compare(Task* task1, Task* task2){
  for (vector<sortKeyword_e>::iterator it = keywords.begin(); it != keywords.end(); it++){
    int x = compareWithKeyword(task1, task2, *it);
    if (x<0) return true;
    if (x>=0) return false;
  }		
  return true;
}
bool Comparer::operator() (Task* task1, Task* task2){
  for (vector<sortKeyword_e>::iterator it = keywords.begin(); it != keywords.end(); it++){
    int x = compareWithKeyword(task1, task2, *it);
    if (x<0) return true;
    if (x>=0) return false;
  }		
  return true;
}
