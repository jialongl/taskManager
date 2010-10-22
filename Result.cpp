/* Author: He Haocong */

#include "Result.h"

Result::Result(){
  isNull = true;
  comparer = new Comparer();
}

Result::Result(TaskList* list, bool detail){
  isNull = false;
  TaskList();
  detailed = detail;
  taskList = list->getTaskMap();
  serialNumberLargest = list->getSerial(); 
  // delete list;
  comparer = new Comparer();
}

Result::~Result(){
  deleteList();
  delete comparer;
}

Result::Result(TaskList* list, Comparer *comp){
  comparer = comp;
  isNull = false;
  TaskList();
  detailed = false;
  taskList = list->getTaskMap();
  serialNumberLargest = list->getSerial();
  // delete list;
}
