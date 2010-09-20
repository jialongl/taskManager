class LsCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command){
		if (command->method = LS){
			vector<Filter*> filters;
			if (command->keyword != "") filters.push_back(new KFilter(command->keyword));
			if (command->finishFlag == YES) filters.push_back(new FFilter(true));
			if (command->finishFlag == NO) filters.push_back(new FFilter(false));
			if (command->group != "") filters.push_back(new GFilter(command->group));
			if (command->overdue) filters.push_back(new OFilter());
			TaskList* list = mainTaskList;
			for (vector<Filter*>::iterator it = filters.begin(); it != filters.end(); it++){
				TaskList* tmp = list->getTasks(*it);
				//delete list;
				list = tmp;
			}
//			cout<<(command->sortKeyword).size()<<endl;
//			cout<<(command->sortKeyword)[(command->sortKeyword).size()]<<endl;
			if ((command->sortKeyword).size()==0) return new Result(list, false);
			else return new Result(list,new Comparer(command->sortKeyword));
		}
		return new Result();
	}
};
