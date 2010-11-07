/* Author: He Haocong */

#include "Shell.h"
Shell::Shell(){
    notuiFlag = false;
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

    agent = new AutoCompletionAgent();
    /*
    vector<string> lexicon;
    lexicon.push_back("morning");
    lexicon.push_back("afternoon");
    lexicon.push_back("important");
    lexicon.push_back("this");
    lexicon.push_back("next");
    lexicon.push_back("add");
    lexicon.push_back("edit");
    lexicon.push_back("task");
    lexicon.push_back("pri");
    lexicon.push_back("finish");
    lexicon.push_back("export");
    lexicon.push_back("import");
    lexicon.push_back("sort");
    lexicon.push_back("run");
    lexicon.push_back("read");
    lexicon.push_back("tui");
    lexicon.push_back("notui");
    lexicon.push_back("undo");
    lexicon.push_back("redo");
    lexicon.push_back("priority");
    lexicon.push_back("deadline");
    lexicon.push_back("serialnumber");
    lexicon.push_back("html");
    lexicon.push_back("tomorrow");
    lexicon.push_back("today");
    lexicon.push_back("week");
    lexicon.push_back("month");
    lexicon.push_back("year");
    lexicon.push_back("monday");
    lexicon.push_back("tuesday");
    lexicon.push_back("wednesday");
    lexicon.push_back("thursday");
    lexicon.push_back("friday");
    lexicon.push_back("saturday");
    lexicon.push_back("sunday");
    lexicon.push_back("january");
    lexicon.push_back("february");
    lexicon.push_back("march");
    lexicon.push_back("april");
    lexicon.push_back("may");
    lexicon.push_back("june");
    lexicon.push_back("july");
    lexicon.push_back("august");
    lexicon.push_back("september");
    lexicon.push_back("october");
    lexicon.push_back("november");
    lexicon.push_back("december");
    int count = lexicon.size();

    for (int i=0; i<count; i++)
        agent->tell(lexicon[i]);
*/
    //msterious bug
    agent->ask("hello there");

    IOModule->echo("Importing task list...");
    Result* result;
    //load saved record.
    try{
        Command* cmd = new Command();
        cmd->method = IMPORT;
        result = executeOneCommand(NULL,cmd);
        //cout<<"get import result, delete import result"<<endl;
        delete result;


    } catch (exception_e except){
        IOModule->handleException(except);
    }
    IOModule->echo("Done\n");

    IOModule->echo("Initializing auto-complete...");
    agent -> analysis(mainTaskList);
    IOModule->echo("Done\n");

//    cout<<"analysis finish"<<endl;
//   cout<< agent->ask("ls")<<endl;
}
Shell::~Shell(){
    //cout<<"deleting main task list"<<endl;
    delete IOModule;
    delete mainTaskList;
    delete mainCommandExecutor;
    delete parser;
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

void Shell::start(string args){
    if (args != "") notuiFlag = true;
    IOModule -> echo("Runing start up script...");
    Command* cmd = new Command();
    Result* result;
    try{
        cmd->method = RUN;
        result = executeOneCommand(NULL,cmd);
        delete result;
    } catch (exception_e except){
        IOModule->handleException(except);
    }
    IOModule -> echo("Done\n");
    if (args == ""){
        mainLoop();
    }
    else{
        CommandList commandList;
        Result *result;
        Command * command;
        try{
            commandList = parser->inputToCommandList(args);

            if (commandList.size()!=0){
                if (typeid(*IOModule) == typeid(PdcIO)) IOModule->echo(commandList[0]->originalCommand);
                result = executeCommandList(commandList);
                IOModule->showOutput(result); 
                if (toChangeIOModule){
                    delete IOModule;
                    IOModule = newIOModule;
                    IOModule->echo("\nDone\n");
                    toChangeIOModule = false;
                }
            }
            else IOModule->echo(" Invalid command");

            command = new Command();
            command->method = EXPORT;
            result = mainCommandExecutor->executeCommand(mainTaskList,command);
            delete result;

        }
        catch (exception_e except){
            if (except == EXCEPTION_HALT) return;
            IOModule->handleException(except);
        }
    }
}

Result* Shell::executeOneCommand(Result* result, Command* command){
    commandMethod mtd = command->method;
    TM_IOModule* newIO ;
    ifstream script;
    Result* ans;
    bool flag;
    if (mtd == ADD || mtd == EDIT){
        agent->analysis(command->taskDescription);
        agent->analysis(command->group);
    }
    int percentage;
    string similar;
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
            ans =  new Result();
            if (typeid(*IOModule) == typeid(PdcIO)) break;
            if (notuiFlag == true) break;
            newIO = new PdcIO(parser,agent);
            changeIOModule(newIO);
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
                while (getline(script, line)){ // '#' starts a line of comment
                    try{
                        CommandList commandList;
                        Command *command;
                        Result *result2;
                        commandMethod mtd;
                        if (line[0] != '#'){
                            commandList = parser->inputToCommandList(line);
                            if (commandList.size()!=0){

                                result2 = executeCommandList(commandList);
                                IOModule->showOutput(result2); 
                  
                                if (toChangeIOModule){
                                     delete IOModule;
                                     IOModule = newIOModule;
                                     IOModule->echo("\nDone\n");
                                     toChangeIOModule = false;
                                }
                            }
                        }
                    
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
                percentage = testSimilarity(command->taskDescription, &similar);    
                flag = true;
                if (percentage >= 70) flag = IOModule->confirm("This task is highly similiar to some existing task:\n  "+similar+"\nDo you really want to add it?");
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
              if (typeid(*IOModule) == typeid(PdcIO)) IOModule->echo(commandList[0]->originalCommand);
              result = executeCommandList(commandList);
              IOModule->showOutput(result); 
              if (toChangeIOModule){
                  delete IOModule;
                  IOModule = newIOModule;
                  IOModule->echo("\nDone\n");
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

    IOModule->showWelcomeMessage();
    while (oneIteration()){
        //run untill exception halt is triggled.
    }

}

void Shell::changeIOModule(TM_IOModule* newIO){
    toChangeIOModule = true;
    newIOModule = newIO;
}
int Shell::testSimilarity(string st, string* similar){
    Comparer* cp = new Comparer;
    vector<Task*> list = mainTaskList->sort(cp);
    int max = 0;
    for (int i=0;i<list.size();i++){
        int x = lcs(list[i]->getDescription(),st);
        if (x>max){
            max = x;
            similar->assign(NumberToString(list[i]->getSerialNumber())+" "+list[i]->getDescription());
        }
    }
    delete cp;
    return max;
}
