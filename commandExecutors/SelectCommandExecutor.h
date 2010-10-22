/* Author: He Haocong */
#ifndef SelectCommandExecutorH
#define SelectCommandExecutorH

#include "commandExecutors/CommandExecutor.h"
#include "filters/Filter.h"
#include "filters/KFilter.h"
#include "filters/FFilter.h"
#include "filters/GFilter.h"
#include "filters/OFilter.h"
#include "Comparer.h"
class SelectCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command);
    Result *executeCommand(Result* result, Command *command);
};
#endif
