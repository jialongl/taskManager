#include "RunCommandExecutor.h"

Result* RunCommandExecutor::executeCommand(TaskList* mainTaskList, Result* result,Command *command){
    return new Result();
}
Result* RunCommandExecutor::executeCommand(TaskList* mainTaskList,Command *command){
    if (command->method == RUN){
        ifstream script((command->filename).c_str());
        if (script.is_open()){
            string line;
            while (getline(script, line)){
              try{
                CommandList commandList;
                Command *command;
                Result *result;

                commandList = parser->inputToCommandList(line);

                result = shell->executeCommandList(commandList);

                if (!(result->isNull))
                    IOModule->showOutput(result); 
                
                command = new Command();
                command->method = EXPORT;
                mainCommandExecutor->executeCommand(command);
                delete command;
              }  

              catch (exception_e except){
                if (except == EXCEPTION_HALT) break;
                IOModule->handleException(except);
              }
            }
        }
    }
    return new Result();
}
