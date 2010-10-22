#include "commandExecutors/PriCommandExecutor.h"
Result* PriCommandExecutor::executeCommand(Command *command){
    if (command->method == PRI){
        int taskNum = (command->serialNumberList)[0];
        mainTaskList->editTaskPriority(taskNum,command->priority);
    }
    return new Result;
}
