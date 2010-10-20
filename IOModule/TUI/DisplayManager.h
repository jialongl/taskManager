#ifndef DisplayManagerH
#define DisplayManagerH
#define StackSize 10
#define KEY_ESC 27
class DisplayManager{
private:
    DisplayElement* escStack[StackSize];
    int escStackTop;
    string keyHistory;
    PdcIO* parent;
public:
    void redraw();
    DisplayManager(PdcIO* parentIO);
    ~DisplayManager();
    void releaseForcus();
    void newElement(DisplayElement* element);
    void handleKey(int ch); 
    void handleResult(Result* result);
    void setCommand(CommandList cl);
};
DisplayManager* displayManager;
#endif
