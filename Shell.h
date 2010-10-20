/* Author: He Haocong */
// For debugging!!!!!!!
class Shell{
private:
    bool toChangeIOModule;
    TM_IOModule* newIOModule;
public:

	void start();
    Result* executeCommandList(CommandList commandList);
    bool oneIteration();		
	void mainLoop();
    void changeIOModule(TM_IOModule* newIO);

};

Shell *shell;
