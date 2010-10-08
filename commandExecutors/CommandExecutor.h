/* Author: He Haocong */
class CommandExecutor{
public:
	virtual Result *executeCommand(Command *command) =0;
	virtual ~CommandExecutor(){};
};
