# Author: Liu Jialong
# Author: He Haocong

OBJECTS= enums.o util.o Task.o Comparer.o Command.o filters/GFilter.o filters/KFilter.o filters/FFilter.o filters/OFilter.o filters/NFilter.o TaskList.o Result.o Parser.o commandExecutors/AddCommandExecutor.o commandExecutors/EditCommandExecutor.o commandExecutors/RmCommandExecutor.o commandExecutors/LsCommandExecutor.o commandExecutors/TaskCommandExecutor.o commandExecutors/PriCommandExecutor.o commandExecutors/FinishCommandExecutor.o commandExecutors/ExportCommandExecutor.o commandExecutors/ImportCommandExecutor.o commandExecutors/MainCommandExecutor.o Shell.o IOModule/KeyboardIOModule.o
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
