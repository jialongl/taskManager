/* Author: He Haocong */
#ifndef AddCommandExecutorH
#define AddCommandExecutorH

#include "CommandExecutor.h"

class AddCommandExecutor:public CommandExecutor{
public:
	Result* executeCommand(Command *command);
	Result* executeCommand(Result *result, Command *command);
};

#endif
