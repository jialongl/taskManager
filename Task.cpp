/* Author: He Haocong */

#include "Task.h"

Task::Task(time_t deadline, int priority, string description, int cronFreq, bool isFinished, int serialNumber, string group){
  setDeadline(deadline);
  setPriority(priority);
  setDescription(description);
  setIsFinished(isFinished);
  setSerialNumber(serialNumber);
  setGroup(group);
}

void Task::setPriority(int x){
  priority = x;
}
void Task::setDescription(string s){
  description = s;
}	
void Task::setDeadline(time_t t){
  deadline = t;
}
void Task::setGroup(string s){
  group = s;
}
void Task::setSerialNumber(int x){
  serialNumber = x;
}
void Task::setIsFinished(bool f){
  isFinished = f;
}
	
time_t Task::getDeadline(){
  return deadline;
}
int Task::getPriority(){
  return priority;
}
string Task::getDescription(){
  return string(description);
}
bool Task::getIsFinished(){
  return isFinished;
}
int Task::getSerialNumber(){
  return serialNumber;
}
string Task::getGroup(){
  return string(group);
}

bool Task::matchKeyword(string keyword){
  return tryMatch(description, keyword);	
}	
