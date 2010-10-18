# Author: Liu Jialong
# Author: He Haocong

all : taskManager

taskManager : main.o
	g++ -lcurses -o taskManager main.o

main.o : main.cpp includes.h enums.h util.h Task.h Comparer.h CronTask.h Command.h CronManager.h filters/Filter.h filters/GFilter.h filters/KFilter.h filters/FFilter.h filters/OFilter.h filters/NFilter.h TaskList.h Result.h Parser.h commandExecutors/CommandExecutor.h commandExecutors/AddCommandExecutor.h commandExecutors/EditCommandExecutor.h commandExecutors/RmCommandExecutor.h commandExecutors/LsCommandExecutor.h commandExecutors/TaskCommandExecutor.h commandExecutors/PriCommandExecutor.h commandExecutors/CronCommandExecutor.h commandExecutors/FinishCommandExecutor.h commandExecutors/ExportCommandExecutor.h commandExecutors/ImportCommandExecutor.h commandExecutors/MainCommandExecutor.h Shell.h init.h IOModule/TM_IOModule.h IOModule/KeyboardIOModule.h
	g++ -c main.cpp

clean:
	rm *.o
	rm taskManager

install:
	cp taskManager /usr/bin
	cp taskManager.1 /usr/share/man/man1

uninstall:
	rm /usr/bin/taskManager
	rm /usr/share/man/man1/taskManager.1
