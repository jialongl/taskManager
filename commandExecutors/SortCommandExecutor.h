/* Author: He Haocong */
#ifndef SortCommandExecutorH
#define SortCommandExecutorH

#include "CommandExecutor.h"
#include "../Comparer.h"

class SortCommandExecutor:public CommandExecutor{
public:
    Result *executeCommand(TaskList* mainTaskList,Command *command);
    Result *executeCommand(TaskList* mainTaskList, Result* result,Command *command);
};
#endif
