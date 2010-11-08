#ifndef KeyboardIOModuleH
#define KeyboardIOModuleH

#include "../includes.h"
#include "../Command.h"
#include "../Result.h"
#include "TM_IOModule.h"

class KeyboardIOModule: public TM_IOModule{
private: 
    Parser* parser;

public:
    KeyboardIOModule(Parser* pser);
    ~KeyboardIOModule();
    CommandList getCommand() ;
    void showOutput(Result* result) ;
    void showWelcomeMessage() ;
    void handleException(exception_e except) ;
    bool confirm(string prompt);
    void echo(string s);
    void displayHelp();
};

#endif
