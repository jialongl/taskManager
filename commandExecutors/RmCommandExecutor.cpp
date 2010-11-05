#include "RmCommandExecutor.h"
Result* RmCommandExecutor::executeCommand(TaskList* mainTaskList,Command *command){
    if (command->method == RM){
        for (vector<int>::iterator it = command->serialNumberList.begin(); it < command->serialNumberList.end();  it++){
            int x=*it;
            mainTaskList->removeTask(x);
        }
        Filter* grp = new GFilter(command->group);
        TaskList* tmp = mainTaskList->getTasks(grp);
        Comparer * cmp = new Comparer();
        vector<Task*> tasks = tmp->sort(cmp);
        for (int i=0;i<tasks.size();i++){
            mainTaskList->removeTask(tasks[i]->getSerialNumber());
        }
        delete grp;
        delete tmp;
        delete cmp;
            
    }
    return new Result();
}
Result* RmCommandExecutor::executeCommand(TaskList* mainTaskList,Result* result, Command* command){
    if (command->method == RM){
        vector<Task*> tasks = result->sort(result->comparer);
        for (int i=0;i<tasks.size();i++){
            mainTaskList->removeTask(tasks[i]->getSerialNumber());
        }
    }
    return new Result();
}
