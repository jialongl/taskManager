#include "KeyboardIOModule.h"
#include "../Parser.h"
KeyboardIOModule::KeyboardIOModule(Parser* pser){
    parser = pser;
}

KeyboardIOModule::~KeyboardIOModule(){
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
    if (result->isNull == false) 
    {
        string outputString  = parser->resultToOutput(result);
        cout<<outputString<<endl;
    }
    else{
    //    cout<<"NULL"<<endl;
    }
    delete result;
}

void KeyboardIOModule::showWelcomeMessage(){
    cout<<" Task Manager V 0.2 "<<endl;
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
void KeyboardIOModule::displayHelp(){
    cout<<"Usage:"<<endl;
    cout<<"\ttaskManager [ subcommand1 ] | [ subcommand2 ] | ..."<<endl;
    cout<<"Subcommands:"<<endl;
    cout<<"\tls \t[ -s \" Keyword1 Keyword2 ...\" ] [ -k Keyword ] [ -f yes/no ] [ -g group ] [ -i t0:t1 ]"<<endl;
    cout<<"\trm \t[ taskNumber1 taskNumber2 taskNumber2 ... ] [ -g group ]"<<endl;
    cout<<"\texport \t[ -html ] filename"<<endl;
    cout<<"\tpri \tserialNumber [ priority ]"<<endl;
    cout<<"\tedit \tserialNumber [ -d \"description\" ] [ -g group ] [ -t time ] [ -p priority ] [ -f yes/no ]"<<endl;
    cout<<"\tmap \t\"customized command\" \"original command\""<<endl;
    cout<<"\tfinish \tserialNumber"<<endl;
    cout<<"\tread \tfilename"<<endl;
    cout<<"\timport \tfilename"<<endl;
    cout<<"\ttask \tserialNumber"<<endl;
    cout<<"\trun \tfilename"<<endl;
    cout<<"\tundo"<<endl;
    cout<<"\tredo"<<endl;
    cout<<"\ttui"<<endl;
    cout<<"\tnotui"<<endl;
    cout<<"\texit"<<endl;
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
    cout<<s;
    cout.flush();
}
