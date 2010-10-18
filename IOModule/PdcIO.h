#ifndef _PdcIO
#define _PdcIO

class PdcIO : public TM_IOModule{
public:
    PdcIO();
    ~PdcIO();

    CommandList getCommand() ;
    void showOutput(Result* result) ;
    void showWelcomeMessage() ;
    void handleException(exception_e except) ;
    bool confirm(string prompt);

};

#endif
