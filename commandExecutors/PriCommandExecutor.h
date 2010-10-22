/* Author: He Haocong */
#ifndef PriCommandExecutorH
#define PriCommandExecutorH

#include "CommandExecutor.h"
class PriCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command);
};

#endif
