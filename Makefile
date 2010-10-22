# Author: Liu Jialong
# Author: He Haocong

OBJECTS=main.o enums.o util.o Task.o Comparer.o CronTask.o Command.o CronManager.o Filter.o GFilter.o KFilter.o FFilter.o OFilter.o NFilter.o TaskList.o Result.o Parser.o commandExecutors/CommandExecutor.o commandExecutors/AddCommandExecutor.o commandExecutors/EditCommandExecutor.o commandExecutors/RmCommandExecutor.o commandExecutors/LsCommandExecutor.o commandExecutors/TaskCommandExecutor.o commandExecutors/PriCommandExecutor.o commandExecutors/CronCommandExecutor.o commandExecutors/FinishCommandExecutor.o commandExecutors/ExportCommandExecutor.o commandExecutors/ImportCommandExecutor.o commandExecutors/MainCommandExecutor.o Shell.o init.o IOModule/TM_IOModule.o IOModule/KeyboardIOModule.o
CFLAGS=-g -Wall

all: taskManager

taskManager: $(OBJECTS)
	$(CC) $(FLAGS) -o taskManager $(OBJECTS)

clean:
	rm taskManager $(OBJECTS)

install:
	cp taskManager /usr/bin
	cp taskManager.1 /usr/share/man/man1

uninstall:
	rm /usr/bin/taskManager
	rm /usr/share/man/man1/taskManager.1
