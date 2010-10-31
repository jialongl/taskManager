/* Author: He Haocong */
#ifndef EditCommandExecutorH
#define EditCommandExecutorH

#include "CommandExecutor.h"

class EditCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(TaskList* mainTaskList,Command *command);
};
#endif
