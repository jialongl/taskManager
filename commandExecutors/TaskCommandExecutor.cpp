#include "TaskCommandExecutor.h"
Result* TaskCommandExecutor::executeCommand(TaskList* mainTaskList,Command *command){
    if (command->method == TASK){
        int taskNum = (command->serialNumberList)[0];
        Filter* nfil = new NFilter(taskNum);
        Result* result = new Result(mainTaskList->getTasks(nfil), true);
        delete nfil; 
        return result;
    }
    return new Result();
}
Result* TaskCommandExecutor::executeCommand(TaskList* mainTaskList,Result *result, Command *command){
    if (command->method == TASK){
        return new Result(result->clone() , true);
    }
    return new Result();
}
