/* Author: He Haocong */
class MainCommandExecutor:public CommandExecutor{
private:
	map<commandMethod, CommandExecutor*> executors;
public:
	~MainCommandExecutor();
	MainCommandExecutor();
	Result *executeCommand(Command *command);
	Result *executeCommand(Result* result, Command *command);
};

MainCommandExecutor *mainCommandExecutor;
