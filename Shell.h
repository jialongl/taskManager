/* Author: Liu Jialong */

#ifndef ShellH
#define ShellH

#include "Result.h"
#include "IOModule/TM_IOModule.h"
#include "Command.h"
#include "commandExecutors/MainCommandExecutor.h"

class Shell{

 private:
  bool toChangeIOModule;
  TM_IOModule* newIOModule;


 public:
  void start();
  Result* executeCommandList(CommandList commandList);
  bool oneIteration();		
  void mainLoop();
  void changeIOModule(TM_IOModule* newIO);

};

Shell *shell;

#endif
