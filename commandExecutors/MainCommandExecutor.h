/* Author: He Haocong */
class MainCommandExecutor:public CommandExecutor{
private:
	map<commandMethod, CommandExecutor*> executors;
public:
	~MainCommandExecutor(){
		for (map<commandMethod, CommandExecutor*>::iterator it = executors.begin(); it != executors.end(); it++){
			delete it->second;
		}
	}
	MainCommandExecutor(){
		executors[ADD] = new AddCommandExecutor();
		executors[FINISH] = new FinishCommandExecutor();
		executors[EDIT] = new EditCommandExecutor();
		executors[EXPORT] = new ExportCommandExecutor();
		executors[IMPORT] = new ImportCommandExecutor();
		executors[PRI] = new PriCommandExecutor();
		executors[LS] = new LsCommandExecutor();
		executors[TASK] = new TaskCommandExecutor();
		executors[RM] = new RmCommandExecutor();
		//executors[CRON] = new CronCommandExecutor();
	}
	Result *executeCommand(Command *command){
		Result* ans =  executors[command->method]->executeCommand(command);
//		delete command;
		return ans;
	}
};

MainCommandExecutor *mainCommandExecutor;
