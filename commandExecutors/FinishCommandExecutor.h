class FinishCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command){
		if (command->method == FINISH) {
			for (vector<int>::iterator it = command->serialNumberList.begin(); it<command->serialNumberList.end(); it++){
				int x=*it;
				mainTaskList->editTaskIsFinished(x, true);
			}
		}
		//cron!!!!!!!!!
		return new Result();
	}
};
