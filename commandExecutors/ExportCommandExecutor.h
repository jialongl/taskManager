/* Author: Wang Xiangyu */
#ifndef ExportCommandExecutorH
#define ExportCommandExecutorH

#include "CommandExecutor.h"

class ExportCommandExecutor: public CommandExecutor
{
public:

    Result* executeCommand (Command* command);
    Result* executeCommand(Result* result, Command *command);
	string distortString (string s);
};
#endif
