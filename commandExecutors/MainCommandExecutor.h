/* Author: He Haocong */
#ifndef MainCommandExecutorH
#define MainCommandExecutorH

#include "CommandExecutor.h"
#include "PriCommandExecutor.h"
#include "AddCommandExecutor.h"
#include "LsCommandExecutor.h"
#include "RunCommandExecutor.h"
#include "EditCommandExecutor.h"
#include "ExportCommandExecutor.h"
#include "ImportCommandExecutor.h"
#include "SelectCommandExecutor.h"
#include "RmCommandExecutor.h"
#include "SortCommandExecutor.h"
#include "TaskCommandExecutor.h"
#include "FinishCommandExecutor.h"

class MainCommandExecutor:public CommandExecutor{
private:
	map<commandMethod, CommandExecutor*> executors;
public:
	~MainCommandExecutor();
	MainCommandExecutor();
	Result *executeCommand(Command *command);
	Result *executeCommand(Result* result, Command *command);
};

MainCommandExecutor *mainCommandExecutor;
#endif
