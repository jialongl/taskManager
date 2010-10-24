/* Author: Zhou Biyan */
#ifndef ReadCommandExecutorH
#define ReadCommandExecutorH

#include "CommandExecutor.h"

class ReadCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(TaskList* mainTaskList, Command *command);
	Result *executeCommand(TaskList* mainTaskList, Result* result, Command *command);
	string restoreString (string s);
	string getNodeContent(string node, string text);
};
#endif
