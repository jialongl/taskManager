/* Author: Liu Jialong */

#ifndef ShellH
#define ShellH

#include "includes.h"
#include "Result.h"
#include "Parser.h"
#include "Command.h"
#include "TaskList.h"
#include "IOModule/TM_IOModule.h"
#include "IOModule/PdcIO.h"
#include "IOModule/KeyboardIOModule.h"
#include "commandExecutors/MainCommandExecutor.h"


class Shell{

 private:
  bool toChangeIOModule;
  TM_IOModule* newIOModule;
  TM_IOModule* IOModule;
  TaskList* mainTaskList;
  Parser* parser;
  MainCommandExecutor* mainCommandExecutor;
  Result* executeOneCommand(Result* result, Command* command);  
  void changeIOModule(TM_IOModule* newIO);
  Result* executeCommandList(CommandList commandList);
  bool oneIteration();		

 public:
  Shell();
  ~Shell();
  void start();
  void mainLoop();

};

#endif
