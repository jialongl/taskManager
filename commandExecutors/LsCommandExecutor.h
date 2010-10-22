/* Author: He Haocong */
#ifndef LsCommandExecutorH
#define LsCommandExecutorH

#include "CommandExecutor.h"
#include "../filters/Filter.h"
#include "../filters/KFilter.h"
#include "../filters/FFilter.h"
#include "../filters/GFilter.h"
#include "../filters/OFilter.h"
#include "../Comparer.h"

class LsCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(TaskList* mainTaskList,Command *command);
    Result *executeCommand(TaskList* mainTaskList, Result* result,Command *command);
};

#endif
