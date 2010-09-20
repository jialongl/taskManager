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
				writeFile<<"	<task>"<<endl;

				//task body
				writeFile<<"		<deadline>"<<iter->second->getDeadline()<<"</deadline>"<<endl;
				writeFile<<"		<priority>"<<iter->second->getPriority()<<"</priority>"<<endl;
				writeFile<<"		<description>"<<description_dist<<"</description>"<<endl;
				writeFile<<"		<cronFreq>"<<iter->second->getCronFreq()<<"</cronFreq>"<<endl;
				writeFile<<"		<isFinished>"<<iter->second->getIsFinished()<<"</isFinished>"<<endl;
				writeFile<<"		<serialNumber>"<<iter->second->getSerialNumber()<<"</serialNumber>"<<endl;
				writeFile<<"		<group>"<<group_dist<<"</group>"<<endl;

				//task end
				writeFile<<"	</task>"<<endl;
			}
			
			//file end
			writeFile<<"</taskList>"<<endl;

			writeFile.close();
		}
		return new Result();
	}

	string distortString (string s)
	{
		int size = s.size();

		for (int i=0; i<size; i++)
		{
			if (s.at(i) == '<' || s.at(i) == '>')
			{
				s[i] = 191;
			}
		}
		return s;
	}
};