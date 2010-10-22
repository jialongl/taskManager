/* Author: He Haocong */
#ifndef FinishCommandExecutorH
#define FinishCommandExecutorH

#include "CommandExecutor.h"
class FinishCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(TaskList* mainTaskList,Command *command);
    Result *executeCommand(TaskList* mainTaskList,Result* result,Command *command);
};
#endif
