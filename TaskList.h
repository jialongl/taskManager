/* Author: He Haocong */
class TaskList{
protected:
	map<int,Task*> taskList;
	int serialNumberLargest;
public:
	TaskList(){
		serialNumberLargest = 0;
		taskList.clear();
	}
	~TaskList(){
		deleteList();
	}

	void deleteList(){
		for (map<int, Task*>::iterator it = taskList.begin(); it!=taskList.end(); it++){
			delete it->second;
		}
	}

	int getSerial(){
		return serialNumberLargest;
	}
	int addTask(Task *task){
		serialNumberLargest++;
		taskList[serialNumberLargest] = task;
		task->setSerialNumber(serialNumberLargest);
		return serialNumberLargest;
	}
	int addTask(int serialNumber, Task* task){
		if (taskList.find(serialNumber) != taskList.end()) throw EXCEPTION_TASK_EXIST;
		taskList[serialNumber] = task;
		if (serialNumber > serialNumberLargest) serialNumberLargest = serialNumber;
		return serialNumber;
	}
	void removeTask(int serialNumber){
		if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
		if ((taskList.find(serialNumber))->second) {
            //delete (taskList.find(serialNumber))->second;
        }
		taskList.erase(taskList.find(serialNumber));	
	}
	void editTaskDeadline(int serialNumber, time_t deadline){
		if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
		taskList[serialNumber]->setDeadline(deadline);
	}
	void editTaskPriority(int serialNumber, int priority){
		if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
		taskList[serialNumber]->setPriority(priority);
	}
	void editTaskDescription(int serialNumber, string description){
		if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
		taskList[serialNumber]->setDescription(description);
	}
	void editTaskCronFreq(int serialNumber, int cronFreq){
		if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
		taskList[serialNumber]->setCronFreq(cronFreq);
	}
	void editTaskIsFinished(int serialNumber, bool isFinished){
		if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
		taskList[serialNumber]->setIsFinished(isFinished);
	}
	void editTaskSerialNumber(int serialNumber, int newSerialNumber){
		if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
		Task* task = taskList[serialNumber];
		taskList.erase(taskList.find(serialNumber));
		taskList[newSerialNumber] = task;
		task->setSerialNumber(newSerialNumber);
		if (newSerialNumber > serialNumberLargest) serialNumberLargest = newSerialNumber;
	}
	void editTaskGroup(int serialNumber, string group){
		if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
		taskList[serialNumber]->setGroup(group);
	}
	map<int, Task*> getTaskMap(){
		map<int, Task*> ans (taskList);
		return ans;
	}
	TaskList* getTasks(Filter* filter){
		TaskList* ans = new TaskList();
		for (map<int,Task*>::iterator it = taskList.begin(); it!=taskList.end(); it++){
			if (filter->filter(it->second)){
				ans->addTask(it->first, it->second);
			}
		}
		
		return ans;
	}
	vector<Task*> sort(Comparer* comp){
		vector<Task*> ans;	
		for (map<int,Task*>::iterator it = taskList.begin(); it!=taskList.end(); it++){
			ans.push_back(it->second);
		}
		for (vector<Task*>::iterator it1 = ans.begin(); it1 != ans.end(); it1++){
			for (vector<Task*>::iterator it2 = it1 + 1; it2 < ans.end(); it2++){
				if (!comp->compare(*it1, *it2)) {
					Task* tmp = *it1;
					*it1 = *it2;
					*it2 = tmp;
				}
			}
		}
		return ans;
	}
    TaskList* clone(){
        TaskList* ans = new TaskList();
        vector<Task*> tasks = sort(new Comparer);
        for (int i=0;i<tasks.size();i++){
            ans->addTask(tasks[i]->getSerialNumber(),tasks[i]);
        }
        return ans;
    }
};
TaskList *mainTaskList;
