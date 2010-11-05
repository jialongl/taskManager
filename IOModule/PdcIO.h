#ifndef PdcIOH
#define PdcIOH

#include "../includes.h"
#ifdef WIN32
    #include "../curses.h"
#else
    #include <ncurses.h>
#endif

#include "../Command.h"
#include "../Result.h"
#include "TM_IOModule.h"
#include "../autocomplete/AutoCompletionAgent.h"

class PdcIO : public TM_IOModule{
private:
    bool commandReady;
    CommandList commandList;
    AutoCompletionAgent* agent;
public:
    Parser* parser;
    PdcIO(Parser* pser, AutoCompletionAgent* acagent);
    ~PdcIO();

    CommandList getCommand() ;
    void showOutput(Result* result) ;
    void showWelcomeMessage() ;
    void handleException(exception_e except) ;
    bool confirm(string prompt);
    void setCommand(CommandList cl);
    void echo(string s);
    
};

#endif
