class MainCommandExecutor:public CommandExecutor{
private:
	map<commandMethod, CommandExecutor*> executors;
public:
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
		return executors[command->method]->executeCommand(command);
	}
};

MainCommandExecutor *mainCommandExecutor;
