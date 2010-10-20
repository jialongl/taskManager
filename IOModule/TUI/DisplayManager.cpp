
DisplayManager::DisplayManager(PdcIO* parentIO){
    parent = parentIO;
    escStack[0] = new ListDisplayElement(mainTaskList);
    escStackTop = 0;
    escStack[0] -> setParent(escStack[0]);
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
        escStack[escStackTop] -> draw();
        refresh();
        if (flag) escStack[escStackTop] -> handleConfirm( false );
    }
    /*else{
        if (ch == 13 || ch == 10){
            string st = keyHistory;
            keyHistory.clear();
            int mx=0, my=0;
            getmaxyx(stdscr, mx, my);
            move(mx - 1,0);
            hline(' ', my);
            CommandList cl =  parser->inputToCommandList(st);
            parent->setCommand(cl);
        }else{
            keyHistory = keyHistory+string(1,(char)ch);
            printw("%c",ch);
            refresh();
        } 
    }*/
    else escStack[escStackTop] -> handleKey(ch);
}

void DisplayManager::redraw(){
    clear();
    curs_set(0);
    mvprintw(0,0,"Task Manager V0.15     TUI with PDCurses");
    mvprintw(1,0," <Ctrl-C> to exit");
    move(3,0);
    int mx=0, my=0;
    getmaxyx(stdscr, mx, my);
    hline('=', my);
    refresh();
    for (int i=0;i<=escStackTop;i++){
        escStack[i] -> draw();
    }
}

void DisplayManager::handleResult(Result* result){
    escStack[escStackTop] -> handleResult(result);
}

void DisplayManager::setCommand(CommandList cl){
    parent->setCommand(cl);
}
