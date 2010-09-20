// For debugging!!!!!!!
#include "debug.h"
class Shell{
public:

	Command *command;
	Result *result;
	string output;		

	void start(){
		cout<<endl;
		cout<<" Task Manager V 0.0 "<<endl;
		cout<<" exit<enter> to quit. help<enter> for more instructions"<<endl;
		cout<<"====================================================================="<<endl;
		mainLoop();
	}
		
	void mainLoop(){
		for (;;){
			try{
				cout<<"> ";
				char str[MAX_LEN];
				cin.getline(str,MAX_LEN);
				cronManager->newTasks(cronManager->lastTime,currentTime());
				command = parser->inputToCommand(str);
				result = mainCommandExecutor->executeCommand(command);
				output = parser->resultToOutput(result);
				cout<< output << endl;
			}
			catch (exception_e except){
				if (except == EXCEPTION_HALT) break;
				if (except == EXCEPTION_NO_SUCH_TASK) cout<<"TaskManager: no such task"<<endl;
				if (except == EXCEPTION_NO_SUCH_COMMAND) cout<<"TaskManager: command not found"<<endl;
			}
		}
	}

};

Shell *shell;
