class TaskList{
private:
	map<int,Task*> taskList;
	int serialNumberLargest;
public:
	TaskList(){
		serialNumberLargest = 0;
		taskList.clear();
	}
	void addTask(Task *task){
		serialNumberLargest++;
		taskList[serialNumberLargest] = task;
	}
	void removeTask(int serialNumber){
		taskList.erase(taskList.find(serialNumber));	
	}
	void editTaskDeadline(int serialNumber, time_t deadline){
		taskList[serialNumber]->setDeadline(deadline);
	}
	void editTaskPriority(int serialNumber, int priority){
		taskList[serialNumber]->setPriority(priority);
	}
	void editTaskDescription(int serialNumber, string description){
		taskList[serialNumber]->setDescription(description);
	}
	void editTaskCronFreq(int serialNumber, int cronFreq){
		taskList[serialNumber]->setCronFreq(cronFreq);
	}
	void editTaskIsFinished(int serialNumber, bool isFinished){
		taskList[serialNumber]->setIsFinished(isFinished);
	}
	void editTaskSerialNumber(int serialNumber, int newSerialNumber){
		taskList[serialNumber]->setSerialNumber(newSerialNumber);
	}
	void editTaskGroup(int serialNumber, string group){
		taskList[serialNumber]->setGroup(group);
	}
	map<int, Task*> getTaskMap(){
		map<int, Task*> ans (taskList);
		return ans;
	}
	map<int, Task*> getTask(Filter* filter){
		map<int, Task*> ans;
		ans.clear();
		for (map<int,Task*>::iterator it = taskList.begin(); it!=taskList.end(); it++){
			if (filter->filter(it->second)) ans[it->first] = it->second;
		}
		return ans;
	}
};
