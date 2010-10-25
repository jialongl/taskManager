/* Author: He Haocong */
#ifndef CommandExecutorH
#define CommandExecutorH

#include "../includes.h"
#include "../Command.h"
#include "../Result.h"
#include "../TaskList.h"

class CommandExecutor{
public:
	virtual Result* executeCommand(TaskList* mainTaskList,Command *command) =0;
	virtual Result* executeCommand(TaskList* mainTaskList, Result* result,Command *command){return new Result();};
	virtual ~CommandExecutor(){};
};
#endif
