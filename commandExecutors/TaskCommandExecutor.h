/* Author: He Haocong */
#ifndef TaskCommandExecutorH
#define TaskCommandExecutorH

#include "CommandExecutor.h"
#include "../filters/NFilter.h"

class TaskCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(TaskList* mainTaskList,Command *command);
    Result *executeCommand(TaskList* mainTaskList,Result *result, Command *command);
};
#endif
