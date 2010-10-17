/* Author: He Haocong */
// For debugging!!!!!!!

void Shell::start(){
        IOModule->showWelcomeMessage();
        mainLoop();
	}

Result* Shell::executeCommandList(CommandList commandList){

	    Result *result;
        
        if (commandList.size() != 0 && commandList[0]->method != NULLCOMMAND)
    		  result = mainCommandExecutor->executeCommand(commandList[0]);
        else 
              result = new Result();

        for (int i=1;i<commandList.size();i++){
              if (commandList[i]->method != NULLCOMMAND)
                  result = mainCommandExecutor->executeCommand(result, commandList[i]);
              else result = new Result();
        }
        
        return result;
    }

bool Shell::oneIteration(){
	    CommandList commandList;
	    Result *result;
        Command * command;

			try{

			  commandList = IOModule->getCommand();

              cout<<commandList.size()<<" commands"<<endl;

              result = executeCommandList(commandList);

			  if (!(result->isNull))
                  IOModule->showOutput(result); 

			  command = new Command();
			  command->method = EXPORT;
			  mainCommandExecutor->executeCommand(command);
			  delete command;
			}
			catch (exception_e except){
				if (except == EXCEPTION_HALT) return false;
				IOModule->handleException(except);
			}

            return true;
    }
		
void Shell::mainLoop(){

    while (oneIteration()){};

};

