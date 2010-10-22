/* Author: He Haocong */
#ifndef SortCommandExecutorH
#define SortCommandExecutorH

#include "commandExecutors/CommandExecutor.h"
#include "Comparer.h"

class SortCommandExecutor:public CommandExecutor{
public:
    Result *executeCommand(Command *command);
    Result *executeCommand(Result* result, Command *command);
};
#endif
