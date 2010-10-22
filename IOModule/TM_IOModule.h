#ifndef TM_IOModuleH
#define TM_IOModuleH

#include "../includes.h"
#include "../Command.h"
#include "../Result.h"

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
