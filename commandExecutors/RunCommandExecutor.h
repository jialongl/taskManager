/* Author: He Haocong */
#ifndef RunCommandExecutorH
#define RunCommandExecutorH

#include "CommandExecutor.h"
#include "../IOModule/TM_IOModule.h"
#include "../Shell.h"

class RunCommandExecutor:public CommandExecutor{
public:
    Result *executeCommand(Command *command);
    Result *executeCommand(Result* result, Command *command);
};
#endif
