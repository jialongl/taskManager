/* Author: He Haocong */
#ifndef RmCommandExecutorH
#define RmCommandExecutorH

#include "commandExecutors/CommandExecutor.h"

class RmCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command);
    Result *executeCommand(Result* result, Command* command);
};
#endif
