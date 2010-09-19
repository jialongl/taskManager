class Result:public TaskList{
public:
	bool detailed;
	bool isNull;
	Result(){
		isNull = true;
	}
	Result(TaskList* list, bool detail){
		TaskList();
		detailed = detail;
		taskList = list->getTaskMap();
		serialNumberLargest = list->getSerial(); 
		delete list;
	}
};
