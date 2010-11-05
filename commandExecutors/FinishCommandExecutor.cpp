#include "FinishCommandExecutor.h"

Result* FinishCommandExecutor::executeCommand(TaskList* mainTaskList,Command *command){
    if (command->method == FINISH) {
        for (vector<int>::iterator it = command->serialNumberList.begin(); it<command->serialNumberList.end(); it++){
            int x=*it;
            mainTaskList->editTaskIsFinished(x, true);
        }
        Filter* grp = new GFilter(command->group);
        TaskList* tmp = mainTaskList->getTasks(grp);
        Comparer * cmp = new Comparer();
        vector<Task*> tasks = tmp->sort(cmp);
        for (int i=0;i<tasks.size();i++){
            mainTaskList->editTaskIsFinished(tasks[i]->getSerialNumber(),true);
        }
        delete grp;
        delete tmp;
        delete cmp;
    }
    return new Result();
}
Result* FinishCommandExecutor::executeCommand(TaskList* mainTaskList,Result* result,Command *command){
    if (command->method == FINISH){
        vector<Task*> tasks = result->sort(result->comparer);
        for (int i=0;i<tasks.size();i++){
            mainTaskList->editTaskIsFinished(tasks[i]->getSerialNumber(),true);
        }
    }
    return new Result();
}
