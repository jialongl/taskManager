/* Author: Liu Jialong */

#ifndef TaskListH
#define TaskListH

#include "includes.h"
#include "Comparer.h"
#include "filters/Filter.h"
#include "Task.h"

class TaskList{
 protected:
  map<int,Task*> taskList;
  int serialNumberLargest;

 public:
  TaskList();
  virtual ~TaskList();

  void deleteList();
  int getSerial();
  int addTask(Task *task);
  int addTask(int serialNumber, Task* task);
  void removeTask(int serialNumber);
  void editTaskDeadline(int serialNumber, time_t deadline);
  void editTaskFinishTime(int serialNumber, time_t finishTime);
  void editTaskPriority(int serialNumber, int priority);
  void editTaskDescription(int serialNumber, string description);
  void editTaskIsFinished(int serialNumber, bool isFinished);
  void editTaskSerialNumber(int serialNumber, int newSerialNumber);
  void editTaskGroup(int serialNumber, string group);
  //map<int, Task*> getTaskMap();
  TaskList* getTasks(Filter* filter);
  vector<Task*> sort(Comparer* comp);
  TaskList* clone();
  void clearEntries();
  void sort(vector<Task*> *a,int l, int r, Comparer* comp);

};

#endif
