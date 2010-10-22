#ifndef cleanUpH
#define cleanUpH

#include "TaskList.h"
#include "Parser.h"
#include "commandExecutors/MainCommandExecutor.h"
#include "IOModule/TM_IOModule.h"
#include "Shell.h"
void cleanUp(){
    delete mainTaskList;
    delete parser;
    delete mainCommandExecutor;
    delete IOModule;
    delete shell;
}
#endif
