class ImportCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command){
		if (command->method == IMPORT){
			delete mainTaskList;

			ifstream record(command->filename);

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
						serialNumber = StringToNum(data.substr(start, end-start));

						getline(record, data); //deadline
						start = data.find("<deadline>") + 10;
						end = data.find("</deadline>");
						deadline = StringToNum(data.substr(start, end-start));

						getline(record, data); //priority
						start = data.find("<priority>") + 10;
						end = data.find("</priority>");
						priority = StringToNum(data.substr(start, end-start));
	
						getline(record, data); //description
						start = data.find("<description>") + 13;
						end = data.find("</description>");
						description = data.substr(start, end-start);

						getline(record, data); //cronFreq
						start = data.find("<cronFreq>") + 10;
						end = data.find("</cronFreq>"); 
						cronFreq = StringToNum(data.substr(start, end-start));

						getline(record, data); //isFinished
						start = data.find("<isFinished>") + 12;
						end = data.find("</isFinished>");
						if(data.substr(start, end-start) == string("true")) isFinished = true;
						else isFinished = false;

						getline(record, data); //group
						start = data.find("<group>") + 7;
						end = data.find("</group>");
						group = data.substr(start, end-start);

						Task* task = new Task(deadline, priority, description, cronFreq, isFinished, serialNumber, group);
						mainTaskList->addTask(task);

						getline(record, data); //</task>
					}			
				}
			}
			
		}
		return new Result();
	}
};

