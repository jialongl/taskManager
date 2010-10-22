/* Author: He Haocong */
#ifndef RmCommandExecutorH
#define RmCommandExecutorH

#include "CommandExecutor.h"

class RmCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(TaskList* mainTaskList,Command *command);
    Result *executeCommand(TaskList* mainTaskList,Result* result, Command* command);
};
#endif
