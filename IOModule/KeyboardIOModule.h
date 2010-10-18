#ifndef _KeyboardIOModule
#define _KeyboardIOModule

class KeyboardIOModule: public TM_IOModule{

public:
    CommandList getCommand() ;
    void showOutput(Result* result) ;
    void showWelcomeMessage() ;
    void handleException(exception_e except) ;
    bool confirm(string prompt);
};

#endif
