#include "AddCommandExecutor.h"

Result* AddCommandExecutor::executeCommand(TaskList* mainTaskList,Command* command){
    if (command->method == ADD){
        Task* newT = new Task(command->deadline,command->priority,command->taskDescription,command->cronFreq,command->finished,0,command->group,NO_SPECIFIC_DEADLINE);
        mainTaskList->addTask(newT);
        delete newT;
    }
    return new Result();
}
Result* AddCommandExecutor::executeCommand(TaskList* mainTaskList,Result *result, Command *command){
    if (command->method == ADD){
        vector<Task *> tasks = result->sort(result->comparer);
        for (int i=0;i<tasks.size();i++){
            mainTaskList->addTask(tasks[i]);
        }
    }
    return new Result();
}
