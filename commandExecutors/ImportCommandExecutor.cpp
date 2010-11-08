/* Author: Zhou Biyan */

#include "ImportCommandExecutor.h"
string ImportCommandExecutor::restoreString (string s){
	int i = 0;
	while (i + 3 < s.size()){
		if(s.substr(i, 4) == "&lt;"){
			s.replace(i, 4, "<");
		}else if(s.substr(i, 4) == "&gt;"){
			s.replace(i, 4, ">");
		}else if(i + 4 < s.size() && s.substr(i, 5) == "&amp;"){
			s.replace(i, 5, "&");
		}else if(i + 5< s.size() && s.substr(i, 6) == "&apos;"){
			s.replace(i, 6, "\'");
		}else if(i + 5< s.size() && s.substr(i, 6) == "&quot;"){
			s.replace(i, 6, "\"");
		}
		i++;
	}

	return s;
}

string ImportCommandExecutor::getNodeContent(string node, string text){
	string content;
	int start, end;
	
	/*if(text.find("<" + node + ">") == sting::npos || text.find("</" + node + ">") == string::npos)
	//throw EXCEPTION_TAG_NOT_FOUND;*/

	start = text.find("<" + node + ">") + node.size() + 2;
	end = text.find("</" + node + ">");
	content = restoreString(text.substr(start, end - start));

//		cout<<node<<"!"<<content<<"!"<<endl;
	return content;
}

Result* ImportCommandExecutor::executeCommand(TaskList* mainTaskList, Command *command){
	if (command->method == IMPORT){
//		delete mainTaskList;
//		mainTaskList = new TaskList();

//		map<int, Task*> tmp = storeMainTaskList->getTaskMap();
//		for (map<int, Task*>::iterator it = tmp.begin(); it != tmp.end(); it++){mainTaskList->addTask(it->first, it->second);}

		if (command->filename == "")
		  command->filename = RECORDFILE;

		  ifstream record((command->filename).c_str());

		string line;
		string data;
		int serialNumber;	
		int deadline;
		int priority;
		string description;
		//int cronFreq;
		bool isFinished;
		string group;
        time_t finishTime;
		
		if (record.is_open()) {

			while(getline(record, line)){data = data + line;}

			while(data.find("<task>") != string::npos){
				serialNumber = mainTaskList->getSerial()+1;
				deadline = StringToNum(getNodeContent("deadline", data));
				priority = StringToNum(getNodeContent("priority", data));
				description = getNodeContent("description", data);
				//cronFreq = StringToNum(getNodeContent("cronFreq", data));
				if(StringToNum(getNodeContent("isFinished", data))) isFinished = true;
				else isFinished = false;
				group = getNodeContent("group", data);

				finishTime = StringToNum(getNodeContent("finishTime", data));

				data.replace(0, data.find("</task>") + 8, " ");

				Task* task = new Task(deadline, priority, description, 0, isFinished, serialNumber, group, finishTime);
				mainTaskList->addTask(serialNumber,task);
                delete task;
			}

		}/*else{
			throw EXCEPTION_FILE_OPEN_FAILED;
		}*/
        //cout<<"clone main task list in import"<<endl;
		return new Result(mainTaskList->clone(),false);
	}
	return new Result();
}

Result* ImportCommandExecutor::executeCommand(TaskList* mainTaskList, Result* result, Command *command){
	if (command->method == IMPORT){
        Comparer* cmp = new Comparer();
		vector<Task*> tmp = result->sort(cmp);
		for (int i=0;i<tmp.size();i++){
			tmp[i]->setSerialNumber(mainTaskList->getSerial()+1);
			mainTaskList->addTask(tmp[i]->getSerialNumber(), tmp[i]);
		}
        delete cmp;
		return new Result(mainTaskList->clone(),false);
	}
	return new Result();
}
