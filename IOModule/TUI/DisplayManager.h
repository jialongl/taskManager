#ifndef DisplayManagerH
#define DisplayManagerH

#ifdef WIN32
    #include "../../curses.h"
#else 
    #include <ncurses.h>
#endif
#include "../../includes.h"
#include "DisplayElement.h"
#include "ListDisplayElement.h"
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
public:
    void redraw();
    DisplayManager(PdcIO* parentIO);
    ~DisplayManager();
    void releaseForcus();
    void newElement(DisplayElement* element);
    void handleKey(int ch); 
    void handleResult(Result* result);
    void setCommand(CommandList cl);
    void echo(string s);
};
DisplayManager* displayManager;
#endif
