#include "commandExecutors/SortCommandExecutor.h"

Result* SortCommandExecutor::executeCommand(Command *command){
    return new Result();
}
Result* SortCommandExecutor::executeCommand(Result* result, Command *command){
    if (command->method == SORT){
        if ((command->sortKeyword).size()==0) return new Result(result, false);
        else return new Result(result,new Comparer(command->sortKeyword));
    }
    return new Result();
}
