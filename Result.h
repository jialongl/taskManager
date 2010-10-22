/* Author: He Haocong */

#ifndef ResultH
#define ResultH

class Result:public TaskList{
 public:
  bool detailed;
  bool isNull;
  Comparer* comparer;

  Result();
  Result(TaskList* list, bool detail);
  ~Result();

  Result(TaskList* list, Comparer *comp);
};

#endif
