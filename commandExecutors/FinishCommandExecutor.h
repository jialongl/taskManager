/* Author: He Haocong */
#ifndef FinishCommandExecutorH
#define FinishCommandExecutorH

#include "CommandExecutor.h"
class FinishCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command);
    Result *executeCommand(Result* result,Command *command);
};
#endif
