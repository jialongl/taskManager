#ifndef _TM_IOModule
#define _TM_IOModule

class TM_IOModule{
public:
    virtual ~TM_IOModule(){};

    virtual CommandList getCommand() {};
    virtual void showOutput(Result* result) {};
    virtual void showWelcomeMessage() {};
    virtual void handleException(exception_e except) {};
    virtual bool confirm(string prompt){};
    virtual void echo(string s){};
};

TM_IOModule* IOModule;

#endif
