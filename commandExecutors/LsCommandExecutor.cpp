#include "LsCommandExecutor.h"

Result* LsCommandExecutor::executeCommand(TaskList* mainTaskList,Command *command){
    if (command->method == LS){
        vector<Filter*> filters;
        if (command->keyword != "") filters.push_back(new KFilter(command->keyword));
        if (command->finishFlag == YES) filters.push_back(new FFilter(true));
        if (command->finishFlag == NO) filters.push_back(new FFilter(false));
        if (command->group != "") filters.push_back(new GFilter(command->group));
        if (command->overdue) filters.push_back(new OFilter());
        if (command->deadline2 != 0) filters.push_back(new IFilter(command->deadline,command->deadline2));
        TaskList* list = mainTaskList->clone();
        for (vector<Filter*>::iterator it = filters.begin(); it != filters.end(); it++){
            TaskList* tmp = list->getTasks(*it);
            delete list;
            list = tmp;
            delete *it;
        }
//			cout<<(command->sortKeyword).size()<<endl;
//			cout<<(command->sortKeyword)[(command->sortKeyword).size()]<<endl;
//        cout<<"goint to return not null result"<<endl;
        if ((command->sortKeyword).size()==0) return new Result(list, false);
        else return new Result(list,new Comparer(command->sortKeyword));
    }
    return new Result();
}
Result* LsCommandExecutor::executeCommand(TaskList* mainTaskList, Result* result,Command *command){
    if (command->method == LS){
        vector<Filter*> filters;
        if (command->keyword != "") filters.push_back(new KFilter(command->keyword));
        if (command->finishFlag == YES) filters.push_back(new FFilter(true));
        if (command->finishFlag == NO) filters.push_back(new FFilter(false));
        if (command->group != "") filters.push_back(new GFilter(command->group));
        if (command->overdue) filters.push_back(new OFilter());
        TaskList* list = (result->isNull)?mainTaskList->clone():result->clone();
        for (vector<Filter*>::iterator it = filters.begin(); it != filters.end(); it++){
            TaskList* tmp = list->getTasks(*it);
            delete list;
            list = tmp;
            delete *it;
        }
        if ((command->sortKeyword).size()==0) return new Result(list, false);
        else return new Result(list,new Comparer(command->sortKeyword));
    }
    return new Result();
}
