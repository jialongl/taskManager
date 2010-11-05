/* Author: He Haocong */

#include "Result.h"

Result::Result(){
//    cout<<"newing result!"<<endl;
    TaskList();
  isNull = true;
  comparer = new Comparer();
}

Result::Result(TaskList* list, bool detail){
 //   cout<<"newing result!"<<endl;
    TaskList();
  isNull = false;
  detailed = detail;
  comparer = new Comparer();
  vector<Task*> tmpV = list->sort(comparer);
  for (int i=0;i<tmpV.size();i++)
      addTask(tmpV[i]->getSerialNumber(),tmpV[i]);
  serialNumberLargest = list->getSerial(); 
  delete list;
}

Result::~Result(){
 //   cout<<"deleting result"<<endl;
  deleteList();
  delete comparer;
}

Result::Result(TaskList* list, Comparer *comp){
  comparer = comp;
  isNull = false;
  detailed = false;
  vector<Task*> tmpV = list->sort(comparer);
  for (int i=0;i<tmpV.size();i++)
      addTask(tmpV[i]->getSerialNumber(),tmpV[i]);
  serialNumberLargest = list->getSerial();
  delete list;
}
