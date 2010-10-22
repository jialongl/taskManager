/* Author: He Haocong */

#ifndef includesH
#define includesH


#define TIMEZONE 8
#define MAX_LEN 1024

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

#ifndef WIN32
  #include <ncurses.h>

#else
  #include "curses.h"

#endif

#include "enums.cpp"
#include "util.cpp"
#include "init.h"


#endif

/*
#include "Task.h"
#include "Comparer.h"
#include "CronTask.h"
#include "Command.h"
#include "CronManager.h"

#include "filters/Filter.h"
#include "filters/GFilter.h"
#include "filters/KFilter.h"
#include "filters/FFilter.h"
#include "filters/OFilter.h"
#include "filters/NFilter.h"

#include "TaskList.h"
#include "Result.h"

#include "IOModule/TM_IOModule.h"
#include "IOModule/KeyboardIOModule.h"
#include "IOModule/PdcIO.h"
#include "IOModule/TUI/DisplayElement.h"
#include "IOModule/TUI/ListDisplayElement.h"
#include "IOModule/TUI/DisplayManager.h"
#include "Shell.h"
#include "Parser.h"
#include "IOModule/KeyboardIOModule.cpp"
#include "IOModule/PdcIO.cpp"
#include "IOModule/TUI/DisplayElement.cpp"
#include "IOModule/TUI/ListDisplayElement.cpp"
#include "IOModule/TUI/DisplayManager.cpp"


#include "commandExecutors/CommandExecutor.h"
#include "commandExecutors/MainCommandExecutor.h"
#include "commandExecutors/AddCommandExecutor.h"
#include "commandExecutors/EditCommandExecutor.h"
#include "commandExecutors/RmCommandExecutor.h"
#include "commandExecutors/LsCommandExecutor.h"//deprecated
#include "commandExecutors/SelectCommandExecutor.h"
#include "commandExecutors/TaskCommandExecutor.h"
#include "commandExecutors/PriCommandExecutor.h"
#include "commandExecutors/CronCommandExecutor.h"
#include "commandExecutors/FinishCommandExecutor.h"
#include "commandExecutors/ExportCommandExecutor.h"
#include "commandExecutors/ImportCommandExecutor.h"
#include "commandExecutors/SortCommandExecutor.h"
#include "commandExecutors/RunCommandExecutor.h"
#include "commandExecutors/MainCommandExecutor.cpp"

#include "Shell.cpp"

#include "cleanUp.cpp"
*/
