/* Author: He Haocong */
#ifndef PriCommandExecutorH
#define PriCommandExecutorH

#include "CommandExecutor.h"
class PriCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(TaskList* mainTaskList,Command *command);
};

#endif
