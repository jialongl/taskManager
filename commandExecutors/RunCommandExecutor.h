/* Author: He Haocong */
class RunCommandExecutor:public CommandExecutor{
public:
    Result *executeCommand(Command *command){
        if (command->method == RUN){
            ifstream script((command->filename).c_str());
            if (script.is_open()){
                string line;
                while (getline(script, line)){
                  try{
                    Command *command;
                    Result *result;
                    command = IOModule->getCommand();
                    if (command->method != NULLCOMMAND){
                        result = mainCommandExecutor->executeCommand(command);
                        IOModule->showOutput(result);
                    }
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
    Result *executeCommand(Result* result, Command *command){
        return new Result();
    }
};
