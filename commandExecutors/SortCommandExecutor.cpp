#include "SortCommandExecutor.h"

Result* SortCommandExecutor::executeCommand(TaskList* mainTaskList,Command *command){
    return new Result();
}
Result* SortCommandExecutor::executeCommand(TaskList* mainTaskList, Result* result,Command *command){
    if (command->method == SORT){
        if ((command->sortKeyword).size()==0) return new Result(result, false);
        else return new Result(result->clone(),new Comparer(command->sortKeyword));
    }
    return new Result();
}
