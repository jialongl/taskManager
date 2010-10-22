/* Author: Wang Xiangyu */
#ifndef ExportCommandExecutorH
#define ExportCommandExecutorH

#include "commandExecutors/CommandExecutor.h"
#include "TaskList.h"

class ExportCommandExecutor: public CommandExecutor
{
public:

    Result* executeCommand (Command* command);
    Result* executeCommand(Result* result, Command *command);
	string distortString (string s);
};
#endif
