/* Author: He Haocong */
class SortCommandExecutor:public CommandExecutor{
public:
    Result *executeCommand(Command *command){
        return new Result();
    }
    Result *executeCommand(Result* result, Command *command){
        if (command->method == SORT){
			if ((command->sortKeyword).size()==0) return new Result(result, false);
			else return new Result(result,new Comparer(command->sortKeyword));
        }
        return new Result();
    }
};
