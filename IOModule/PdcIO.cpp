#include "PdcIO.h"
#include "TUI/DisplayManager.h"

PdcIO::PdcIO(Parser* pser){
        commandReady = false;
        parser = pser;
        initscr();
		refresh();
        raw();
        keypad(stdscr, TRUE);
        noecho();
        displayManager = new DisplayManager(this);
}

PdcIO::~PdcIO(){
        delete displayManager;
        clear();
        endwin();
}

CommandList PdcIO::getCommand(){
    displayManager->redraw();
    int ch;
    int mx=0, my=0;
    while (!commandReady){
        ch = getch();
        if (ch == 3)  setCommand(parser->inputToCommandList("exit"));
        else if (ch == (int)'Q') setCommand(parser->inputToCommandList("notui"));
        else displayManager -> handleKey(ch);
    }

    commandReady = false;
    return commandList;
}

void PdcIO::showOutput(Result* result){
  displayManager -> handleResult(result);
}

void PdcIO::showWelcomeMessage(){
}
    
void PdcIO::handleException(exception_e except){
  /*
    if (except == EXCEPTION_NO_SUCH_TASK) cout<<"TaskManager: no such task"<<endl;
    if (except == EXCEPTION_NO_SUCH_COMMAND) cout<<"TaskManager: command not found"<<endl;
    if (except == EXCEPTION_TASK_EXIST) cout<<"TaskManager: add task failed. task exists"<<endl;
    if (except == EXCEPTION_ILLEGAL_EXPRESSION) cout<<"TaskManager: illegal expression"<<endl;
    if (except == EXCEPTION_HELP) displayHelp();
  */
}

bool PdcIO::confirm(string prompt){
    vector<string> lines;
    while (prompt.length()>0){
        int x=0,y=0;
        while (x<30){
            if (prompt[x] == ' ') y=x;
            x++;
        }
        lines.push_back(prompt.substr(0,y));
        prompt.erase(0,y);
    }
    int mx,my;
    getmaxyx(stdscr,mx,my);
    int height = lines.size() + 3;
    int width = 34;
    int startRow = (mx-height)/2;
    int startCol = (my-width)/2;
    for (int i=0;i<height;i++){
        move(startRow+i,startCol-1);
        if (i==0) printw(" +--------------------------------+ ");
        else if (i==height-1) printw(" +--------------------------------+ ");
        else printw(" |%32s| "," ");
    }
    attron(A_BOLD);
    for (int i=0;i<lines.size();i++){
        move(startRow+i+1,startCol+2);
        printw("%s",(lines[i]).c_str());
    }
    attroff(A_BOLD);
    int colYes = 12;
    int colNo = 19; 
    bool flag = false;
    move(startRow+lines.size()+1,startCol+colYes);
    if (flag) attron(A_REVERSE);
    printw("Yes");
    if (flag) attroff(A_REVERSE);
    move(startRow+lines.size()+1,startCol+colNo);
    if (!flag) attron(A_REVERSE);
    printw("No ");
    if (!flag) attroff(A_REVERSE);

    bool finished = false;
    while (!finished){
        int ch=getch();
        switch (ch){
            case 10:
            case 13:
                finished = true;
                break;
            case KEY_LEFT:
                flag = true;
                break;
            case KEY_RIGHT:
                flag = false;
                break;
            default:
                break;
        }
        move(startRow+lines.size()+1,startCol+colYes);
        if (flag) attron(A_REVERSE);
        printw("Yes");
        if (flag) attroff(A_REVERSE);
        move(startRow+lines.size()+1,startCol+colNo);
        if (!flag) attron(A_REVERSE);
        printw("No ");
        if (!flag) attroff(A_REVERSE);
    } 
    move(0,my);
    return flag;
}

void PdcIO::setCommand(CommandList cl){
    commandReady = true;
    commandList = cl;
}

void PdcIO::echo(string s){
    displayManager->echo(s);    
}
