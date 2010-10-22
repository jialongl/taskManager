/* Author: He Haocong */
#include "MainCommandExecutor.h"
MainCommandExecutor::~MainCommandExecutor(){
		for (map<commandMethod, CommandExecutor*>::iterator it = executors.begin(); it != executors.end(); it++){
			delete it->second;
		}
	}
MainCommandExecutor::MainCommandExecutor(){
		executors[ADD] = new AddCommandExecutor();
		executors[FINISH] = new FinishCommandExecutor();
		executors[EDIT] = new EditCommandExecutor();
		executors[EXPORT] = new ExportCommandExecutor();
		executors[IMPORT] = new ImportCommandExecutor();
		executors[PRI] = new PriCommandExecutor();
		executors[LS] = new LsCommandExecutor();// deprecated
		executors[SELECT] = new SelectCommandExecutor();
		executors[TASK] = new TaskCommandExecutor();
        executors[RM] = new RmCommandExecutor();
		executors[SORT] = new SortCommandExecutor();
		executors[RUN] = new RunCommandExecutor();
		//executors[CRON] = new CronCommandExecutor();
	}
Result* MainCommandExecutor::executeCommand(Command *command){
	  if ( command->method != NULLCOMMAND)
	    return executors[command->method]->executeCommand(command);
	  else
	    return new Result();
	}

Result* MainCommandExecutor::executeCommand(Result* result, Command *command){
    if ( command->method != NULLCOMMAND)
	    return executors[command->method]->executeCommand(result, command);
	  else
	    return new Result();
}
