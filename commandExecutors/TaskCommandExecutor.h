/* Author: He Haocong */
#ifndef TaskCommandExecutorH
#define TaskCommandExecutorH

#include "commandExecutors/CommandExecutor.h"
#include "filters/NFilter.h"

class TaskCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command);
    Result *executeCommand(Result *result, Command *command);
};
#endif
