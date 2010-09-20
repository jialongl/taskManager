class Result:public TaskList{
public:
	bool detailed;
	bool isNull;
	Comparer* comparer;
	Result(){
		isNull = true;
	}
	Result(TaskList* list, bool detail){
		isNull = false;
		TaskList();
		detailed = detail;
		taskList = list->getTaskMap();
		serialNumberLargest = list->getSerial(); 
		delete list;
		comparer = new Comparer();
	}
	Result(TaskList* list, Comparer *comp){
		comparer = comp;
		isNull = false;
		TaskList();
		detailed = false;
		taskList = list->getTaskMap();
		serialNumberLargest = list->getSerial();
		delete list;
	}	

};
