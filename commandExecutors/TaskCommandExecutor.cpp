#include "TaskCommandExecutor.h"
Result* TaskCommandExecutor::executeCommand(TaskList* mainTaskList,Command *command){
    if (command->method == TASK){
        int taskNum = (command->serialNumberList)[0];
        return new Result(mainTaskList->getTasks(new NFilter(taskNum)), true);
    }
    return new Result();
}
Result* TaskCommandExecutor::executeCommand(TaskList* mainTaskList,Result *result, Command *command){
    if (command->method == TASK){
        return new Result(result , true);
    }
    return new Result();
}
