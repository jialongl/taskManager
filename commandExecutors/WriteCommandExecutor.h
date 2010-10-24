/* Author: Zhou Biyan */
#include <fstream>
#ifndef WriteCommandExecutorH
#define WriteCommandExecutorH

#include "CommandExecutor.h"

class WriteCommandExecutor: public CommandExecutor{
public:
	Result *executeCommand (TaskList* mainTaskList, Command* command);
	Result *executeCommand(TaskList* mainTaskList, Result* result, Command *command);
	string distortString (string s);
};
#endif
