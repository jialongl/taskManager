#include "RmCommandExecutor.h"
Result* RmCommandExecutor::executeCommand(Command *command){
    if (command->method == RM){
        for (vector<int>::iterator it = command->serialNumberList.begin(); it < command->serialNumberList.end();  it++){
            int x=*it;
            mainTaskList->removeTask(x);
        }
        map<int, Task*> tmp = mainTaskList->getTaskMap();
        for (map<int, Task*>::iterator it = tmp.begin(); it != tmp.end(); it++){
            if ((it->second)->getGroup() == command->group) mainTaskList->removeTask(it->first);
        }
            
    }
    return new Result();
}
Result* RmCommandExecutor::executeCommand(Result* result, Command* command){
    if (command->method == RM){
        map<int, Task*> tmp = result->getTaskMap();
        for (map<int, Task*>::iterator it = tmp.begin(); it != tmp.end(); it++){
           mainTaskList->removeTask((it->second)->getSerialNumber());
        }
    }
    return new Result();
}
