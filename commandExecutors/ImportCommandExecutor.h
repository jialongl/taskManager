class ImportCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command){
		if (command->method == IMPORT){
			delete mainTaskList;
			mainTaskList = new TaskList();

			ifstream record("test.xml");//((command->filename).c_str());

			string data;
			int serialNumber;	
			int deadline;
			int priority;
			string description;
			int cronFreq;
			bool isFinished;
			string group;
			int start, end;

			if (record.is_open() && getline(record, data)) {
				while (getline(record, data) && data.find("</taskList>") == string::npos) { //<task>
					if(data.find("<task>")){
						getline(record, data); //serialNumber
						start = data.find("<serialNumber>") + 14;
						end = data.find("</serialNumber>");
						serialNumber = StringToNum(restoreString(data.substr(start, end-start)));

						getline(record, data); //deadline
						start = data.find("<deadline>") + 10;
						end = data.find("</deadline>");
						deadline = StringToNum(restoreString(data.substr(start, end-start)));

						getline(record, data); //priority
						start = data.find("<priority>") + 10;
						end = data.find("</priority>");
						priority = StringToNum(restoreString(data.substr(start, end-start)));
	
						getline(record, data); //description
						start = data.find("<description>") + 13;
						end = data.find("</description>");
						description = restoreString(data.substr(start, end-start));

						getline(record, data); //cronFreq
						start = data.find("<cronFreq>") + 10;
						end = data.find("</cronFreq>"); 
						cronFreq = StringToNum(restoreString(data.substr(start, end-start)));

						getline(record, data); //isFinished
						start = data.find("<isFinished>") + 12;
						end = data.find("</isFinished>");
						if(restoreString(data.substr(start, end-start)) == string("true")) isFinished = true;
						else isFinished = false;

						getline(record, data); //group
						start = data.find("<group>") + 7;
						end = data.find("</group>");
						group = restoreString(data.substr(start, end-start));

						Task* task = new Task(deadline, priority, description, cronFreq, isFinished, serialNumber, group);
						mainTaskList->addTask(task->getSerialNumber(),task);

						getline(record, data); //</task>
					}			
				}
			}
			
		}
		return new Result();
	}

	string restoreString (string s){
		int i = 0;
		while (i != s.size()){
			if (s.at(i) == '\\'){
				s.replace (i, i+1, "");
				i++;
			}
			i++;
		}
		return s;
	}
};

