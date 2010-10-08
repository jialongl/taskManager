/* Author: He Haocong */
// For debugging!!!!!!!
#include "debug.h"
class Shell{
public:

	Command *command;
	Result *result;
	string output;		

	void start(){
		cout<<" Task Manager V 0.1 "<<endl;
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
				command = new Command();
				command->method = EXPORT;
				mainCommandExecutor->executeCommand(command);
			}
			catch (exception_e except){
				if (except == EXCEPTION_HALT) break;
				if (except == EXCEPTION_NO_SUCH_TASK) cout<<"TaskManager: no such task"<<endl;
				if (except == EXCEPTION_NO_SUCH_COMMAND) cout<<"TaskManager: command not found"<<endl;
				if (except == EXCEPTION_TASK_EXIST) cout<<"TaskManager: add task failed. task exists"<<endl;
				if (except == EXCEPTION_ILLEGAL_EXPRESSION) cout<<"TaskManager: illegal expression"<<endl;
				if (except == EXCEPTION_HELP) displayHelp();
			}
		}
	}

};

Shell *shell;
