#ifndef KeyboardIOModuleH
#define KeyboardIOModuleH

#include "../includes.h"
#include "../Command.h"
#include "../Result.h"
#include "../Parser.h"

class KeyboardIOModule: public TM_IOModule{

public:
    CommandList getCommand() ;
    void showOutput(Result* result) ;
    void showWelcomeMessage() ;
    void handleException(exception_e except) ;
    bool confirm(string prompt);
};

#endif
