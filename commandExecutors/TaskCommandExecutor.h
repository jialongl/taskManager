class TaskCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command){
		if (command->method == TASK){
			int taskNum = (command->serialNumberList)[0];
			return new Result(mainTaskList->getTasks(new NFilter(taskNum)), true);
		}
	}
};
