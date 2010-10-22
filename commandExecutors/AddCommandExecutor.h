/* Author: He Haocong */
#ifndef AddCommandExecutorH
#define AddCommandExecutorH

#include "CommandExecutor.h"

class AddCommandExecutor:public CommandExecutor{
public:
	Result* executeCommand(TaskList* mainTaskList,Command *command);
	Result* executeCommand(TaskList* mainTaskList,Result *result, Command *command);
};

#endif
