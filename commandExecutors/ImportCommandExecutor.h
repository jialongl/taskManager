/* Author: Zhou Biyan */
#ifndef ImportCommandExecutorH
#define ImportCommandExecutorH

#include "CommandExecutor.h"
class ImportCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(TaskList* mainTaskList,Command *command);
	Result *executeCommand(TaskList* mainTaskList, Result* result,Command *command);
	string restoreString (string s);
	string getNodeContent(string node, string text);
};
#endif
