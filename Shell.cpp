/* Author: He Haocong */

#include "Shell.h"
Shell::Shell(){
    //initiallize function units.
    mainTaskList = new TaskList();
    mainCommandExecutor = new MainCommandExecutor();
    parser = new Parser();
    IOModule = new KeyboardIOModule(parser);
    toChangeIOModule = false;
    //load saved record.
    Command* cmd = new Command();
    cmd->method = IMPORT;

    try{
        executeOneCommand(NULL,cmd);
    } catch (exception_e except){
        IOModule->handleException(except);
    }
}
Shell::~Shell(){
    delete mainTaskList;
    delete mainCommandExecutor;
    delete parser;
    delete IOModule;
}

void Shell::start(){
    IOModule->showWelcomeMessage();
    mainLoop();
}

Result* Shell::executeOneCommand(Result* result, Command* command){
    TM_IOModule* newIO ;
    ifstream script;
    //handle special command when low level command executor don't have privillige to do it.
    switch (command->method){
        case NULLCOMMAND: //invalid command
            return new Result();
        case TUI: //enable text UI
            newIO = new PdcIO(parser);
            changeIOModule(newIO);
            return new Result();
            break;
        case NOTUI: //disable text UI
            newIO = new KeyboardIOModule(parser);
            changeIOModule(newIO);
            return new Result();
            break;
        case RUN: //run a TM script

	    if(command->filename == "")
	      command->filename = RECORDFILE;

            script.open((command->filename).c_str());
            if (script.is_open()){
                string line;
                while (getline(script, line)){
                    try{
                        CommandList commandList;
                        Command *command;
                        Result *result;

                        commandList = parser->inputToCommandList(line);
                        result = executeCommandList(commandList);

                        if (!(result->isNull))
                        IOModule->showOutput(result); 
                    
                        command = new Command();
                        command->method = EXPORT;
                        mainCommandExecutor->executeCommand(mainTaskList,command);
                        delete command;
                    }  

                    catch (exception_e except){
                        if (except == EXCEPTION_HALT) break;
                            IOModule->handleException(except);
                    }
                }
            }
            script.close();
            return new Result();
            break;
        default:
            return (result == NULL)?mainCommandExecutor->executeCommand(mainTaskList,command):mainCommandExecutor->executeCommand(mainTaskList,result,command);
    }
}
Result* Shell::executeCommandList(CommandList commandList){
    Result *result;
    //execute the first command 
    if (commandList.size() != 0 && commandList[0]->method != NULLCOMMAND)
        result = executeOneCommand(NULL, commandList[0]);
    else 
        result = new Result();
    //execute rest piped comands
    for (int i=1;i<commandList.size();i++){
        result = executeOneCommand(result,commandList[i]);    
    }
    return result;
}

bool Shell::oneIteration(){
    CommandList commandList;
    Result *result;
    Command * command;
    try{
        // get command from IOModule
          commandList = IOModule->getCommand();
        // output the command
          if (commandList.size()!=0) IOModule->echo(commandList[0]->originalCommand);
          else IOModule->echo(" Invalid command");
        // run the command 
          result = executeCommandList(commandList);
        // output the command
          if (!(result->isNull))
              IOModule->showOutput(result); 
        // check if TUI/NOTUI triggled.
          if (toChangeIOModule){
              delete IOModule;
              IOModule = newIOModule;
              toChangeIOModule = false;
          }
        // save record.
          command = new Command();
          command->method = EXPORT;
          mainCommandExecutor->executeCommand(mainTaskList,command);
          delete command;

        }
        catch (exception_e except){
            if (except == EXCEPTION_HALT) return false;
            IOModule->handleException(except);
        }

        return true;
}
		
void Shell::mainLoop(){

    while (oneIteration()){
        //run untill exception halt is triggled.
    }

}

void Shell::changeIOModule(TM_IOModule* newIO){
    toChangeIOModule = true;
    newIOModule = newIO;
}

