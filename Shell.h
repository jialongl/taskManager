/* Author: He Haocong */
// For debugging!!!!!!!
#include "debug.h"
class Shell{
public:

	static void start(){
        /*
		cout<<" Task Manager V 0.1 "<<endl;
		cout<<" exit<enter> to quit. help<enter> for more instructions"<<endl;
		cout<<"====================================================================="<<endl;
        */
        IOModule->showWelcomeMessage();
        mainLoop();
	}
		
	static void mainLoop(){

	    Command *command;
	    Result *result;

		for (;;){
			try{
                /*				
				cout<<"> ";
				char str[MAX_LEN];
				cin.getline(str,MAX_LEN);
                */


			  command = IOModule->getCommand();
//				cronManager->newTasks(cronManager->lastTime,currentTime());
//				command = parser->inputToCommand(inputString);
			  result = mainCommandExecutor->executeCommand(command);

//				string outputString = parser->resultToOutput(result);
			  if (command->method != NULLCOMMAND)               
			    IOModule->showOutput(result); 
                /*
				cout<< output << endl;
                */

			  command = new Command();
			  command->method = EXPORT;
			  mainCommandExecutor->executeCommand(command);
			  delete command;
			}
			catch (exception_e except){
				if (except == EXCEPTION_HALT) break;
				IOModule->handleException(except);
                /*
				if (except == EXCEPTION_NO_SUCH_TASK) cout<<"TaskManager: no such task"<<endl;
				if (except == EXCEPTION_NO_SUCH_COMMAND) cout<<"TaskManager: command not found"<<endl;
				if (except == EXCEPTION_TASK_EXIST) cout<<"TaskManager: add task failed. task exists"<<endl;
				if (except == EXCEPTION_ILLEGAL_EXPRESSION) cout<<"TaskManager: illegal expression"<<endl;
				if (except == EXCEPTION_HELP) displayHelp();
                */
			}
		}
	}

};

//Shell *shell;
