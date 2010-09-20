class EditCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command){
		if (command->method == EDIT){
			int taskNum = (command->serialNumberList)[0];
			if (command->taskDescription != "") mainTaskList->editTaskDescription(taskNum,command->taskDescription);
			if (command->deadline != 0) mainTaskList->editTaskDeadline(taskNum,command->deadline);
			if (command->priority != -100) mainTaskList->editTaskPriority(taskNum,command->priority);
			if (command->group != "") mainTaskList->editTaskGroup(taskNum,command->group);
			if (command->cronFreq != -1) mainTaskList->editTaskCronFreq(taskNum,command->cronFreq);
		}
		return new Result();
	}
};
