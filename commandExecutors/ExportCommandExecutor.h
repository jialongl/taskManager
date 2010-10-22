/* Author: Wang Xiangyu */
#ifndef ExportCommandExecutorH
#define ExportCommandExecutorH

#include "CommandExecutor.h"

class ExportCommandExecutor: public CommandExecutor
{
public:

    Result* executeCommand(TaskList* mainTaskList,Command* command);
    Result* executeCommand(TaskList* mainTaskList, Result* result,Command *command);
	string distortString (string s);
};
#endif
