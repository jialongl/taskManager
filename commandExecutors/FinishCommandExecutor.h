/* Author: He Haocong */
class FinishCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command){
		if (command->method == FINISH) {
			for (vector<int>::iterator it = command->serialNumberList.begin(); it<command->serialNumberList.end(); it++){
				int x=*it;
				mainTaskList->editTaskIsFinished(x, true);
			}
			map<int, Task*> tmp = mainTaskList->getTaskMap();
			for (map<int, Task*>::iterator it = tmp.begin(); it != tmp.end(); it++){
				if ((it->second)->getGroup() == command->group) mainTaskList->editTaskIsFinished(it->first,true);
			}
		}
		//cron!!!!!!!!!
		return new Result();
	}

};
