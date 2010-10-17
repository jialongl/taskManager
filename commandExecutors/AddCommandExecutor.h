/* Author: He Haocong */
class AddCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command){
		if (command->method == ADD){
			mainTaskList->addTask(new Task(command->deadline,command->priority,command->taskDescription,command->cronFreq,command->finished,0,command->group));
			// cron!!!!!!!!!!!! 
		}
		return new Result();
	}
	Result *executeCommand(Result *result, Command *command){
		if (command->method == ADD){
            vector<Task *> tasks = result->sort(result->comparer);
            for (int i=0;i<tasks.size();i++){
			    mainTaskList->addTask(tasks[i]);
            }
			// cron!!!!!!!!!!!! 
		}
		return new Result();
	}
};
