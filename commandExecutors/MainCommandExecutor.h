/* Author: He Haocong */
#ifndef MainCommandExecutorH
#define MainCommandExecutorH

#include "CommandExecutor.h"
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
#endif
