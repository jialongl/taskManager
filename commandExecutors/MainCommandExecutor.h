class MainCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command){
		return new Result();
	}
};

MainCommandExecutor *mainCommandExecutor;
