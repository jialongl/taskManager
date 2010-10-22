/* Author: Zhou Biyan */
#ifndef ImportCommandExecutorH
#define ImportCommandExecutorH

#include "commandExecutors/CommandExecutor.h"
class ImportCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command);
	Result *executeCommand(Result* result, Command *command);
	string restoreString (string s);
	string getNodeContent(string node, string text);
};
#endif
