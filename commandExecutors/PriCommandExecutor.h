/* Author: He Haocong */
#ifndef PriCommandExecutorH
#define PriCommandExecutorH

#include "commandExecutors/CommandExecutor.h"
class PriCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command);
};

#endif
