#ifndef _TM_IOModule
#define _TM_IOModule

class TM_IOModule{
public:
    virtual Command* getCommand() {return new Command();};
    virtual void showOutput(Result* result) {};
    virtual void showWelcomeMessage() {};
    virtual void handleException(exception_e except) {};
};

TM_IOModule* IOModule;

#endif
