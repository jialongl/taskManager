/* Author: He Haocong */

#include "Shell.h"
Shell::Shell(){
    //initiallize function units.
    //cout<<"new main task list"<<endl;
    mainTaskList = new TaskList();
    undoStackTop = 1;
    //cout<<"new undoStack 0"<<endl;
    undoStack[0] = mainTaskList->clone();
    redoStackTop = 0;
    mainCommandExecutor = new MainCommandExecutor();
    parser = new Parser();
    IOModule = new KeyboardIOModule(parser);
    toChangeIOModule = false;
    IOModule->showWelcomeMessage();


    Result* result;
    //load saved record.
    try{
        Command* cmd = new Command();
        cmd->method = IMPORT;
        result = executeOneCommand(NULL,cmd);
        //cout<<"get import result, delete import result"<<endl;
        delete result;

        cmd = new Command();
        cmd->method = RUN;
        result = executeOneCommand(NULL,cmd);
        delete result;
    } catch (exception_e except){
        IOModule->handleException(except);
    }

    agent = new AutoCompletionAgent();

    agent -> analysis(mainTaskList);

    int count = 23;
    string lexicon[] = {
        "add",
        "edit",
        "task",
        "pri",
        "finish",
        "export",
        "import",
        "sort",
        "run",
        "read",
        "tui",
        "notui",
        "undo",
        "redo",
        "priority",
        "deadline",
        "serialnumber",
        "html",
        "tomorrow",
        "today",
        "week",
        "month",
        "year",
    };
    for (int i=0; i<count; i++)
        agent->tell(lexicon[i]);

//    cout<<"analysis finish"<<endl;
 //   cout<< agent->ask("enabl")<<endl;
}
Shell::~Shell(){
    //cout<<"deleting main task list"<<endl;
    delete mainTaskList;
    delete mainCommandExecutor;
    delete parser;
    delete IOModule;
    for (int i=0;i<redoStackTop;i++){
        delete redoStack[i];
    }
    for (int i=0;i<undoStackTop;i++){
        //cout<<"deleting undoStack #"<<i<<endl;
        delete undoStack[i];
    }
}

void Shell::backup(){
    //cout<<"making backup #"<<undoStackTop<<endl;
    undoStack[undoStackTop++] = mainTaskList->clone();
    //cout<<"backup finish"<<endl;
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
    undoStack[undoStackTop++] = redoStack[--redoStackTop];
    delete mainTaskList;
    mainTaskList = undoStack[undoStackTop-1]->clone();
}

void Shell::start(){
    mainLoop();
}

Result* Shell::executeOneCommand(Result* result, Command* command){
    commandMethod mtd = command->method;
    TM_IOModule* newIO ;
    ifstream script;
    Result* ans;
    bool flag;
    //handle special command when low level command executor don't have privillige to do it.
    switch (command->method){
       case UNDO:
            if (result != NULL) delete result;
            delete command;
            undo();
            ans = new Result();
            break;
        case REDO:
            if (result != NULL) delete result;
            delete command;
            redo();
            ans = new Result();
            break;
        case NULLCOMMAND: //invalid command
            if (result != NULL) delete result;
            delete command;
            ans =  new Result();
            break;
        case TUI: //enable text UI
            if (result != NULL) delete result;
            delete command;
            newIO = new PdcIO(parser,agent);
            changeIOModule(newIO);
            ans =  new Result();
            break;
        case NOTUI: //disable text UI
            if (result != NULL) delete result;
            delete command;
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
            if (result != NULL) delete result;
            delete command;

            if (script.is_open()){
                string line;
                while (getline(script, line) && line[0] != '#'){ // '#' starts a line of comment
                    try{
                        CommandList commandList;
                        Command *command;
                        Result *result2;

                        commandList = parser->inputToCommandList(line);
                        if (commandList.size()!=0){

                            result2 = executeCommandList(commandList);
                            IOModule->showOutput(result2); 
              
                            if (toChangeIOModule){
                                 delete IOModule;
                                 IOModule = newIOModule;
                                 toChangeIOModule = false;
                            }
                        }
                    
                        command = new Command();
                        command->method = EXPORT;
                        result2 = mainCommandExecutor->executeCommand(mainTaskList,command);
                        delete result2;
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
            if (command->method == ADD){
                int percentage = testSimilarity(command->taskDescription);    
                flag = true;
                if (percentage >= 70) flag = IOModule->confirm("This task is highly similiar to some existing task, do you really want to add it?");
                if (flag) ans =  (result == NULL)?  mainCommandExecutor->executeCommand(mainTaskList,command):
                                                mainCommandExecutor->executeCommand(mainTaskList,result,command);
                else{
                    delete command;
                    if (result!=NULL) delete result;
                    ans = new Result();
                }
            } else ans =  (result == NULL)? mainCommandExecutor->executeCommand(mainTaskList,command):
                                            mainCommandExecutor->executeCommand(mainTaskList,result,command);
//            cout<<command->method<<endl;
    }

    if (mtd != LS && mtd != NULLCOMMAND && mtd !=EXPORT && mtd != UNDO && mtd != REDO && mtd != TUI && mtd != NOTUI && mtd != READ && mtd != TASK){
        backup();
    }

//    if (ans->isNull) cout<<"is null in exe one c"<<endl;
    
    return ans;
}

Result* Shell::executeCommandList(CommandList commandList){
    Result *result;
    //execute the first command 
    if (commandList.size() != 0 )
        result = executeOneCommand(NULL, commandList[0]);
    else {
        result = new Result();
    }
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
//          cout<<"!!get"<<endl;
        // output the command
          if (commandList.size()!=0){
              IOModule->echo(commandList[0]->originalCommand);
              result = executeCommandList(commandList);
              IOModule->showOutput(result); 
              if (toChangeIOModule){
                  delete IOModule;
                  IOModule = newIOModule;
                  toChangeIOModule = false;
              }
          }
          else IOModule->echo(" Invalid command");
        // save record.
          command = new Command();
          command->method = EXPORT;
          result = mainCommandExecutor->executeCommand(mainTaskList,command);
          delete result;

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
int Shell::testSimilarity(string st){
    Comparer* cp = new Comparer;
    vector<Task*> list = mainTaskList->sort(cp);
    int max = 0;
    for (int i=0;i<list.size();i++){
        int x = lcs(list[i]->getDescription(),st);
        if (x>max) max = x;
    }
    delete cp;
    return max;
}
