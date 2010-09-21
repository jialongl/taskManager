#include <fstream>

class ExportCommandExecutor: public CommandExecutor
{
public:
	Result *executeCommand (Command* command)
	{
		//export to file record.xml
		if (command->method == EXPORT)
		{
			map<int, Task*> tasks = mainTaskList->getTaskMap();
			
			ofstream writeFile("record.xml");

			//file head
			writeFile<<"<taskList>"<<endl;

			//file body
			for (map<int, Task*>::iterator iter = tasks.begin(); iter!=tasks.end(); iter++)
			{
				string description = iter->second->getDescription();
				string group = iter->second->getGroup();

				string group_dist = distortString (group);
				string description_dist = distortString (description);
				//task head
				writeFile<<"	 <task>"<<endl;

				//task body
				//write SN
				writeFile<<"		 <serialNumber>"<<endl;
				writeFile<<"			"<<iter->second->getSerialNumber()<<endl;
				writeFile<<"		 </serialNumber>"<<endl;
				//write deadline
				writeFile<<"		 <deadline>"<<endl;
				writeFile<<"			"<<iter->second->getDeadline()<<endl;
				writeFile<<"		 </deadline>"<<endl;
				//write priority
				writeFile<<"		 <priority>"<<endl;
				writeFile<<"			"<<iter->second->getPriority()<<endl;
				writeFile<<"		 </priority>"<<endl;
				//write description
				writeFile<<"		 <description>"<<endl;
				writeFile<<"			"<<description_dist<<endl;
				writeFile<<"		 </description>"<<endl;
				//write cronFreq
				writeFile<<"		 <cronFreq>"<<endl;
				writeFile<<"			"<<iter->second->getCronFreq()<<endl;
				writeFile<<"		 </cronFreq>"<<endl;
				//write isFinished
				writeFile<<"		 <isFinished>"<<endl;
				writeFile<<"			"<<iter->second->getIsFinished()<<endl;
				writeFile<<"		 </isFinished>"<<endl;
				//write group
				writeFile<<"		 <group>"<<endl;
				writeFile<<"			"<<group_dist<<endl;
				writeFile<<"		 </group>"<<endl;

				//task end
				writeFile<<"	 </task>"<<endl;
			}
			
			//file end
			writeFile<<"</taskList>"<<endl;

			writeFile.close();
		}
		return new Result();
	}

	string distortString (string s)
	{
		int i = 0;
		while (i != s.size())
		{
			if (s.at(i) == '<' || s.at(i) == '>' || s.at(i) == '\\')
			{
				s.insert (i, "\\");
				i++;
			}
			i++;
		}
		return s;
	}
};
