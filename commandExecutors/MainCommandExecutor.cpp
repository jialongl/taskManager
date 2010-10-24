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
		executors[TASK] = new TaskCommandExecutor();
		executors[RM] = new RmCommandExecutor();
		executors[READ] = new ReadCommandExecutor();
		executors[WRITE] = new WriteCommandExecutor();

		// executors[SELECT] = new SelectCommandExecutor();
		// executors[SORT] = new SortCommandExecutor();
		// executors[RUN] = new RunCommandExecutor();
		// executors[CRON] = new CronCommandExecutor();
	}
Result* MainCommandExecutor::executeCommand(TaskList* mainTaskList,Command *command){
	  if ( command->method != NULLCOMMAND)
	    return executors[command->method]->executeCommand(mainTaskList,command);
	  else
	    return new Result();
	}

Result* MainCommandExecutor::executeCommand(TaskList* mainTaskList, Result* result,Command *command){
    if ( command->method != NULLCOMMAND)
	    return executors[command->method]->executeCommand(mainTaskList,result, command);
	  else
	    return new Result();
}
