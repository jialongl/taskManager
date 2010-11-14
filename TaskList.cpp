/* Author: He Haocong */

#include "TaskList.h"

TaskList::TaskList(){
  serialNumberLargest = 0;
  taskList.clear();
//  cout<<"newing task list"<<endl;
}

TaskList::~TaskList(){
//    cout<<"deleting task list"<<endl;
  deleteList();
}

void TaskList::deleteList(){
    clearEntries();
}

int TaskList::getSerial(){
  return serialNumberLargest;
}

int TaskList::addTask(Task *task){
//    cout<<"adding task"<<endl;
  serialNumberLargest++;
  Task* tmpTask = task->clone();
  taskList[serialNumberLargest] = tmpTask;
  tmpTask->setSerialNumber(serialNumberLargest);
  return serialNumberLargest;
}

int TaskList::addTask(int serialNumber, Task* task){
//    cout<<"adding task with sn "<<serialNumber<<endl;
  if (taskList.find(serialNumber) != taskList.end()) throw EXCEPTION_TASK_EXIST;
  taskList[serialNumber] = task->clone();
  if (serialNumber > serialNumberLargest) serialNumberLargest = serialNumber;
  return serialNumber;
}

void TaskList::removeTask(int serialNumber){
  if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
  if ((taskList.find(serialNumber))->second) {
    delete (taskList.find(serialNumber))->second;
  }
  taskList.erase(taskList.find(serialNumber));	
}
void TaskList::editTaskDeadline(int serialNumber, time_t deadline){
  if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
  taskList[serialNumber]->setDeadline(deadline);
}
void TaskList::editTaskFinishTime(int serialNumber, time_t finishTime){
  if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
  taskList[serialNumber]->setFinishTime(finishTime);
}

void TaskList::editTaskPriority(int serialNumber, int priority){
  if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
  taskList[serialNumber]->setPriority(priority);
}

void TaskList::editTaskDescription(int serialNumber, string description){
  if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
  taskList[serialNumber]->setDescription(description);
}


void TaskList::editTaskIsFinished(int serialNumber, bool isFinished){
  if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
  taskList[serialNumber]->setIsFinished(isFinished);
}

void TaskList::editTaskSerialNumber(int serialNumber, int newSerialNumber){
  if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
  Task* task = taskList[serialNumber];
  taskList.erase(taskList.find(serialNumber));
  taskList[newSerialNumber] = task;
  task->setSerialNumber(newSerialNumber);
  if (newSerialNumber > serialNumberLargest) serialNumberLargest = newSerialNumber;
}

void TaskList::editTaskGroup(int serialNumber, string group){
  if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
  taskList[serialNumber]->setGroup(group);
}
/*
map<int, Task*> TaskList::getTaskMap(){
    map<int, Task*> ans;
    for (map<int,Task*>::iterator it = taskList.begin(); it!=taskList.end(); it++){
        ans[it->first]= (it->second)->clone();
    }
  return ans;
}
*/
TaskList* TaskList::getTasks(Filter* filter){
  TaskList* ans = new TaskList();
  for (map<int,Task*>::iterator it = taskList.begin(); it!=taskList.end(); it++){
    if (filter->filter(it->second)){
      ans->addTask(it->first, (it->second));
    }
  }
  ans -> setSerial(serialNumberLargest);
  return ans;
}
vector<Task*> TaskList::sort(Comparer* comp){
  vector<Task*> ans;	
  for (map<int,Task*>::iterator it = taskList.begin(); it!=taskList.end(); it++){
    ans.push_back(it->second);
  }
  if (comp->isNull == true) return ans;
//  std::sort(ans.begin(),ans.end(),*comp);
  /*
  for (vector<Task*>::iterator it1 = ans.begin(); it1 != ans.end(); it1++){
    for (vector<Task*>::iterator it2 = it1 + 1; it2 < ans.end(); it2++){
      if (!comp->compare(*it1, *it2)) {
	Task* tmp = *it1;
	*it1 = *it2;
	*it2 = tmp;
      }
    }
  }
  */
  sort(&ans,0,ans.size()-1,comp);
  return ans;
}

void TaskList::sort(vector<Task*> *a,int l, int r, Comparer* comp){
//    cout<<l<<" "<<r<<endl;
    int p, i=l, j=r;
    if (l<r){
        p = (l+r+1)/2;
        Task* x=(*a)[p];
        while (i<=j){
            while (i<(*a).size() && comp->compare((*a)[i],x)) i++;
            while (j>=0 && (comp->compare(x,(*a)[j]))) j--;
            if (i<=j){
                Task* tmp = (*a)[i];
                (*a)[i] = (*a)[j];
                (*a)[j] = tmp;
                i++;
                j--;
            }
        }
        if (l<j) sort(a,l,j,comp);
        if (i<r) sort(a,i,r,comp);
    }
}

TaskList* TaskList::clone(){
  TaskList* ans = new TaskList();
  Comparer *cp = new Comparer;
  vector<Task*> tasks = sort(cp);
  for (int i=0;i<tasks.size();i++){
    ans->addTask(tasks[i]->getSerialNumber(),tasks[i]);
  }
//  cout<<"cloned tl largest sn: "<<ans->getSerial()<<endl;
  delete cp;
  ans -> setSerial(serialNumberLargest);
  return ans;
}

void TaskList::setSerial(int sn){
    serialNumberLargest = sn;
}

void TaskList::clearEntries(){
  for (map<int, Task*>::iterator it = taskList.begin(); it!=taskList.end(); it++){
    delete it->second;
//    taskList.erase(it);
  }
  taskList.clear();
}

