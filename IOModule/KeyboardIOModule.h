#ifndef _KeyboardIOModule
#define _KeyboardIOModule

class KeyboardIOModule: public TM_IOModule{
public:
    Command* getCommand(){
        cout<<"> ";
        string str;
        getline(cin,str);
        return parser->inputToCommand(str);
 //       return new Command();
    }

    void showOutput(Result* result){
        string outputString  = parser->resultToOutput(result);
        cout<<outputString<<endl;
    }

    void showWelcomeMessage(){
		cout<<" Task Manager V 0.1 "<<endl;
		cout<<" exit<enter> to quit. help<enter> for more instructions"<<endl;
		cout<<"====================================================================="<<endl;
    }
    
    void handleException(exception_e except){
				if (except == EXCEPTION_NO_SUCH_TASK) cout<<"TaskManager: no such task"<<endl;
				if (except == EXCEPTION_NO_SUCH_COMMAND) cout<<"TaskManager: command not found"<<endl;
				if (except == EXCEPTION_TASK_EXIST) cout<<"TaskManager: add task failed. task exists"<<endl;
				if (except == EXCEPTION_ILLEGAL_EXPRESSION) cout<<"TaskManager: illegal expression"<<endl;
				if (except == EXCEPTION_HELP) displayHelp();
    }
    bool confirm(string prompt){
        cout<<prompt;
        string keyIn;
        cin>>keyIn;
        if (keyIn == "Yes" || keyIn == "YES" || keyIn == "Y" || keyIn == "y"){
            return true;
        }
        else return false;
    }
};

#endif
