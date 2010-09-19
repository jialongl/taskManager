class TaskList{
protected:
	map<int,Task*> taskList;
	int serialNumberLargest;
public:
	TaskList(){
		serialNumberLargest = 0;
		taskList.clear();
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
	void removeTask(int serialNumber){
		if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
		delete (taskList.find(serialNumber))->second;
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
		taskList[serialNumber]->setSerialNumber(newSerialNumber);
	}
	void editTaskGroup(int serialNumber, string group){
		if (taskList.find(serialNumber) == taskList.end()) throw EXCEPTION_NO_SUCH_TASK;
		taskList[serialNumber]->setGroup(group);
	}
	map<int, Task*> getTaskMap(){
		map<int, Task*> ans (taskList);
		return ans;
	}
	map<int, Task*> getTasks(Filter* filter){
		map<int, Task*> ans;
		ans.clear();
		for (map<int,Task*>::iterator it = taskList.begin(); it!=taskList.end(); it++){
			if (filter->filter(it->second)) ans[it->first] = it->second;
		}
		return ans;
	}
};
TaskList *mainTaskList;
