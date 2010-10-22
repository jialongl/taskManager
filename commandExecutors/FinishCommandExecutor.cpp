#include "commandExecutors/FinishCommandExecutor.h"

Result* FinishCommandExecutor::executeCommand(Command *command){
    if (command->method == FINISH) {
        for (vector<int>::iterator it = command->serialNumberList.begin(); it<command->serialNumberList.end(); it++){
            int x=*it;
            mainTaskList->editTaskIsFinished(x, true);
        }
        map<int, Task*> tmp = mainTaskList->getTaskMap();
        for (map<int, Task*>::iterator it = tmp.begin(); it != tmp.end(); it++){
            if ((it->second)->getGroup() == command->group) mainTaskList->editTaskIsFinished(it->first,true);
        }
    }
    return new Result();
}
Result* FinishCommandExecutor::executeCommand(Result* result,Command *command){
    if (command->method == FINISH){
        map<int, Task*> tmp = mainTaskList->getTaskMap();
        for (map<int, Task*>::iterator it = tmp.begin(); it != tmp.end(); it++){
           mainTaskList->editTaskIsFinished((it->second)->getSerialNumber() , true);
        }
    }
    return new Result();
}
