#include "KeyboardIOModule.h"
#include "../Parser.h"
KeyboardIOModule::KeyboardIOModule(Parser* pser){
    parser = pser;
}
CommandList KeyboardIOModule::getCommand(){
    cout<<"> ";
    string str;
    if ( getline(cin,str))
      return parser->inputToCommandList(str);
    else
      return parser->inputToCommandList("exit");
}

void KeyboardIOModule::showOutput(Result* result){
    string outputString  = parser->resultToOutput(result);
    cout<<outputString<<endl;
}

void KeyboardIOModule::showWelcomeMessage(){
    cout<<" Task Manager V 0.1 "<<endl;
    cout<<" exit<enter> to quit. help<enter> for more instructions"<<endl;
    cout<<"====================================================================="<<endl;
}
    
void KeyboardIOModule::handleException(exception_e except){
            if (except == EXCEPTION_NO_SUCH_TASK) cout<<"TaskManager: no such task"<<endl;
            if (except == EXCEPTION_NO_SUCH_COMMAND) cout<<"TaskManager: command not found"<<endl;
            if (except == EXCEPTION_TASK_EXIST) cout<<"TaskManager: add task failed. task exists"<<endl;
            if (except == EXCEPTION_ILLEGAL_EXPRESSION) cout<<"TaskManager: illegal expression"<<endl;
            if (except == EXCEPTION_HELP) displayHelp();
}
bool KeyboardIOModule::confirm(string prompt){
    cout<<"TaskManager: "<<prompt<<" ";
    string keyIn;
    getline(cin,keyIn);
    if (keyIn == "Yes" || keyIn == "YES" || keyIn == "Y" || keyIn == "y" || keyIn == "yes"){
        return true;
    }
    else return false;
}
void KeyboardIOModule::echo(string s){
//    cout<<s<<endl;
}
