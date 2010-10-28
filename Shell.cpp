/* Author: He Haocong */

#include "Shell.h"
Shell::Shell(){
    //initiallize function units.
    mainTaskList = new TaskList();
    undoStackTop = 1;
    undoStack[0] = mainTaskList->clone();
    redoStackTop = 0;
    mainCommandExecutor = new MainCommandExecutor();
    parser = new Parser();
    IOModule = new KeyboardIOModule(parser);
    toChangeIOModule = false;
	IOModule->showWelcomeMessage();
    //load saved record.
    
    try{
		Command* cmd = new Command();
		cmd->method = IMPORT;
        executeOneCommand(NULL,cmd);
		delete cmd;
		cmd = new Command();
		cmd->method = RUN;
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
    for (int i=0;i<redoStackTop;i++){
        delete redoStack[i];
    }
    for (int i=0;i<redoStackTop;i++){
        delete undoStack[i];
    }
}

void Shell::backup(){
    undoStack[undoStackTop++] = mainTaskList->clone();
    for (int i=0;i<redoStackTop;i++){
        delete redoStack[i];
    }
    redoStackTop = 0;
}
void Shell::undo(){
    if (undoStackTop <= 1) {
        throw EXCEPTION_UNDO_FAIL;
        return;
    }
    redoStack[redoStackTop++] = undoStack[--undoStackTop];
    delete mainTaskList;
    mainTaskList = undoStack[undoStackTop-1]->clone();
}
void Shell::redo(){
    if (redoStackTop <=0){
        throw EXCEPTION_REDO_FAIL;
        return;
    }
    cout<<"redo"<<endl;
    undoStack[undoStackTop++] = redoStack[--redoStackTop];
    delete mainTaskList;
    mainTaskList = undoStack[undoStackTop-1]->clone();
}

void Shell::start(){
    mainLoop();
}

Result* Shell::executeOneCommand(Result* result, Command* command){
    TM_IOModule* newIO ;
    ifstream script;
    Result* ans;
    //handle special command when low level command executor don't have privillige to do it.
    switch (command->method){
       case UNDO:
            undo();
            ans = new Result();
            break;
        case REDO:
            redo();
            ans = new Result();
            break;
        case NULLCOMMAND: //invalid command
            ans =  new Result();
        case TUI: //enable text UI
            newIO = new PdcIO(parser);
            changeIOModule(newIO);
            ans =  new Result();
            break;
        case NOTUI: //disable text UI
            newIO = new KeyboardIOModule(parser);
            changeIOModule(newIO);
            ans =  new Result();
            break;
        case RM: //remove a task, ask for confirmation

            if (IOModule->confirm("Do you really want to remove this task permanently? "))
                ans =  (result == NULL)?mainCommandExecutor->executeCommand(mainTaskList,command):mainCommandExecutor->executeCommand(mainTaskList,result,command);
            else throw EXCEPTION_CANCEL;

            break;
        case RUN: //run a TM script

	    if(command->filename == "")
	      command->filename = RCFILE;

            script.open((command->filename).c_str());
            if (script.is_open()){
                string line;
                while (getline(script, line)){
                    try{
                        CommandList commandList;
                        Command *command;
                        Result *result;

                        commandList = parser->inputToCommandList(line);
                        if (commandList.size()!=0) result = executeCommandList(commandList);
                        else result = new Result();

                        if (!(result->isNull))
                            IOModule->showOutput(result); 
          
                        if (toChangeIOModule){
                             delete IOModule;
                             IOModule = newIOModule;
                             toChangeIOModule = false;
                        }
                    
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
            ans = new Result();
            break;
        default:
            ans =  (result == NULL)?mainCommandExecutor->executeCommand(mainTaskList,command):mainCommandExecutor->executeCommand(mainTaskList,result,command);
    }

    if (command->method != LS && command->method != NULLCOMMAND && command->method !=EXPORT && command->method != UNDO && command->method != REDO){
        backup();
    }
    return ans;
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

