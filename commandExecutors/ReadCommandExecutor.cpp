/* Author: Zhou Biyan */

#include "ReadCommandExecutor.h"
string ReadCommandExecutor::restoreString (string s){
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

string ReadCommandExecutor::getNodeContent(string node, string text){
	string content;
	int start, end;
	
	/*if(text.find("<" + node + ">") == sting::npos || text.find("</" + node + ">") == string::npos)
	//throw EXCEPTION_TAG_NOT_FOUND;*/

	start = text.find("<" + node + ">") + node.size() + 2;
	end = text.find("</" + node + ">");
	content = restoreString(text.substr(start, end - start));

	return content;
}

Result* ReadCommandExecutor::executeCommand(TaskList* mainTaskList, Command *command){
	if (command->method == READ){
		TaskList * readTaskList = new TaskList();

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
		
		if (record.is_open()) {

			while(getline(record, line)){data = data + line;}

			while(data.find("<task>") != string::npos){
				serialNumber = StringToNum(getNodeContent("serialNumber", data));
				deadline = StringToNum(getNodeContent("deadline", data));
				priority = StringToNum(getNodeContent("priority", data));
				description = getNodeContent("description", data);
				//cronFreq = StringToNum(getNodeContent("cronFreq", data));
				if(StringToNum(getNodeContent("isFinished", data))) isFinished = true;
				else isFinished = false;
				group = getNodeContent("group", data);

				data.replace(0, data.find("</task>") + 8, " ");

				Task* task = new Task(deadline, priority, description, 0, isFinished, serialNumber, group);
				readTaskList->addTask(serialNumber,task);
			}

		}/*else{
			throw EXCEPTION_FILE_OPEN_FAILED;
		}*/
		return new Result(readTaskList,true);
	}
	return new Result();
}

Result* ReadCommandExecutor::executeCommand(TaskList* mainTaskList, Result* result, Command *command){
	if (command->method == READ){
		TaskList * readTaskList = new TaskList();

		map<int, Task*> tmp = result->getTaskMap();
		for (map<int, Task*>::iterator it = tmp.begin(); it != tmp.end(); it++){readTaskList->addTask(it->first, it->second);}

		return new Result(readTaskList,true);
	}
	return new Result();
}
