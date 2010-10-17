/* Author: He Haocong */
class CommandExecutor{
public:
	virtual Result *executeCommand(Command *command) =0;
	virtual Result *executeCommand(Result* result, Command *command){};
	virtual ~CommandExecutor(){};
};
