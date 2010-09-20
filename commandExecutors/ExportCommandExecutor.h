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
				//task head
				writeFile<<"	<task>"<<endl;

				//task body
				writeFile<<"		<deadline>"<<iter->second->getDeadline()<<"</deadline>"<<endl;
				writeFile<<"		<priority>"<<iter->second->getPriority()<<"</priority>"<<endl;
				writeFile<<"		<description>"<<iter->second->getDescription()<<"</description>"<<endl;
				writeFile<<"		<cronFreq>"<<iter->second->getCronFreq()<<"</cronFreq>"<<endl;
				writeFile<<"		<isFinished>"<<iter->second->getIsFinished()<<"</isFinished>"<<endl;
				writeFile<<"		<serialNumber>"<<iter->second->getSerialNumber()<<"</serialNumber>"<<endl;
				writeFile<<"		<group>"<<iter->second->getGroup()<<"</group>"<<endl;

				//task end
				writeFile<<"	</task>"<<endl;
			}
			
			//file end
			writeFile<<"</taskList>"<<endl;

			writeFile.close();
		}
		return new Result();
	}
};