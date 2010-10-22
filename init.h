/* Author: He Haocong */

#ifndef initH
#define initH

#include "Shell.h"
#include "commandExecutors/MainCommandExecutor.h"
#include "Parser.h"
#include "TaskList.h"
#include "Command.h"

void init(){
  shell = new Shell();	
  mainCommandExecutor = new MainCommandExecutor();
  parser = new Parser();
  IOModule = new KeyboardIOModule();
  mainTaskList = new TaskList();
  Command *cmd = new Command();
  cmd->method = IMPORT;

  try{
    mainCommandExecutor->executeCommand(cmd);

  } catch (exception_e except){
    IOModule->handleException(except);
    /*
      if (except == EXCEPTION_NO_SUCH_TASK) cout<<"TaskManager: no such task"<<endl;
      if (except == EXCEPTION_NO_SUCH_COMMAND) cout<<"TaskManager: command not found"<<endl;
      if (except == EXCEPTION_TASK_EXIST) cout<<"TaskManager: add task failed. task exists"<<endl;
      if (except == EXCEPTION_ILLEGAL_EXPRESSION) cout<<"TaskManager: illegal expression"<<endl;
      if (except == EXCEPTION_HELP) displayHelp();
    */
  }
}

#endif
