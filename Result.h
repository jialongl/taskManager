/* Author: He Haocong */

#ifndef ResultH
#define ResultH

#include "TaskList.h"

class Result:public TaskList{
 public:
  bool detailed;
  bool isNull;
  Comparer* comparer;

  Result();
  Result(TaskList* list, bool detail);
  virtual ~Result();

  Result(TaskList* list, Comparer *comp);
};

#endif
