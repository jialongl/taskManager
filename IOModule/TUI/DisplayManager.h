#ifndef DisplayManagerH
#define DisplayManagerH

#ifdef WIN32
    #include "../../curses.h"
#else 
    #include <ncurses.h>
#endif
#include "../../includes.h"
#include "DisplayElement.h"
#include "../PdcIO.h"


#define StackSize 10
#define KEY_ESC 27

class DisplayManager{
 private:
    DisplayElement* escStack[StackSize];
    int escStackTop;
    string keyHistory;
    PdcIO* parent;
    string echoHistory;
    bool initializing;

 public:
    AutoCompletionAgent* agent;
    DisplayManager(PdcIO* parentIO, AutoCompletionAgent* acagent);
    ~DisplayManager();
    void redraw();
    void releaseForcus();
    void newElement(DisplayElement* element);
    void handleKey(int ch); 
    void handleKey(int ch,int count); 
    void handleResult(Result* result);
    void setCommand(CommandList cl);
    void echo(string s);
    void echo(string s, chtype attr);
    void showHelp();
    void enterCommand();
};

static DisplayManager* displayManager;

#endif
