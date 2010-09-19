class AddCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command){
		if (command->method == ADD){
			mainTaskList->addTask(new Task(command->deadline,command->priority,command->taskDescription,command->cronFreq,command->finished,0,command->group));
			// cron!!!!!!!!!!!! 
		}
		return new Result();
	}
};
