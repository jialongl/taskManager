class MainCommandExecutor:public CommandExecutor{
private:
	map<commandMethod, CommandExecutor*> executors;
public:
	MainCommandExecutor(){
		executors[ADD] = new AddCommandExecutor();
		executors[FINISH] = new FinishCommandExecutor();
	}
	Result *executeCommand(Command *command){
		return executors[command->method]->executeCommand(command);
	}
};

MainCommandExecutor *mainCommandExecutor;
