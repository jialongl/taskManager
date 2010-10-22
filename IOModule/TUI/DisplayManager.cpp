#include "DisplayManager.h"
#include "ListDisplayElement.h"

DisplayManager::DisplayManager(PdcIO* parentIO){
    parent = parentIO;
    setCommand((parent->parser)->inputToCommandList("ls"));
    escStack[0] = new ListDisplayElement(new TaskList(),(parent->parser),this);
    escStackTop = 0;
    escStack[0] -> setParent(escStack[0]);
    echoHistory = "";
    redraw();
}
DisplayManager::~DisplayManager(){
    for (int i=0;i<=escStackTop;i++){
        delete escStack[i];       
    }
    curs_set(1);
}
void DisplayManager::releaseForcus(){
    if (escStackTop != 0) escStackTop--;
    escStack[escStackTop] -> draw();
    refresh();
}
void DisplayManager::newElement(DisplayElement* element){
    escStack[++escStackTop] = element;
    element -> setParent(escStack[escStackTop - 1]);
    element -> draw();
    refresh();
}
void DisplayManager::handleKey(int ch){
    if (ch == KEY_ESC) {
        bool flag = false;
        if (escStack[escStackTop] -> type == CONFIRM_DE) flag = true; 
        if (escStackTop != 0) delete escStack[escStackTop];
        releaseForcus();
        if (escStackTop ==0){ 
            escStack[escStackTop] -> reset();
        }
        escStack[escStackTop] -> draw();
        if (escStackTop ==0){ 
            (dynamic_cast<ListDisplayElement*>(escStack[0])) -> restoreLastView();
        }
        refresh();
        if (flag) escStack[escStackTop] -> handleConfirm( false );
    }else if(ch == -1){
        redraw();
    }
    else escStack[escStackTop] -> handleKey(ch);
}

void DisplayManager::redraw(){
    int mx=0, my=0;
    getmaxyx(stdscr, mx, my);
    clear();
    curs_set(0);
    string title = "Task Manager V0.15     TUI with PDCurses";
    int ypos = (my - title.length()) / 2;
    attron(A_REVERSE);
    mvhline(0,0,'-', my);
    mvprintw(0,ypos,title.c_str());
    attroff(A_REVERSE);
    int numOfButtons = 13;
    string buttons[] = {"Ctrl-C","f","d","e","a","SPACE","j","k","up","down","Q","s","ESC"};
    string funcs[] = {"exit","finish","remove","edit","add","show/hide detail","scroll down","scroll up","select previous task","select next task","switch off TUI","search","main task list"};

    int col = 0;
    int row = 1;
    int numOfSpace = 8;
    for (int i=0;i<numOfButtons;i++){
        if (col+numOfSpace+buttons[i].size()+funcs[i].size() >= my){ row++; col=0;}
        move (row,col);
        printw("    <");
        attron(A_BOLD);
        printw("%s",buttons[i].c_str());
        attroff(A_BOLD);
        printw(">: %s",funcs[i].c_str());
        col =col+numOfSpace+buttons[i].size()+funcs[i].size(); 
    }

    refresh();
    (dynamic_cast<ListDisplayElement*>(escStack[0])) -> resize(row+1);
    for (int i=0;i<=escStackTop;i++){
        escStack[i] -> draw();
    }
    (dynamic_cast<ListDisplayElement*>(escStack[0])) -> restoreLastView();
    echo(echoHistory);
}

void DisplayManager::handleResult(Result* result){
    escStack[escStackTop] -> handleResult(result);
}

void DisplayManager::setCommand(CommandList cl){
    parent->setCommand(cl);
}

void DisplayManager::echo(string s){
    echoHistory = s;
    int my,mx;
    getmaxyx(stdscr,mx,my);
    move(mx - 1,0);
    hline(' ',my);
    move(mx - 1,0);
    attron(A_BOLD);
    printw("%s",s.c_str());
    attroff(A_BOLD);
    refresh();
}
