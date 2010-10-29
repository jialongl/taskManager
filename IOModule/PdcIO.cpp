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
    int count = 0;
    while (!commandReady){
        ch = getch();
        if (ch>=48 && ch<58){
            count = count*10+ch-48;
        }
        else{
            if (count == 0) count =1;
            for (int i=0;i<count;i++)
                if (ch == 3)  setCommand(parser->inputToCommandList("exit"));
                else if (ch == (int)'Q') setCommand(parser->inputToCommandList("notui"));
                else displayManager -> handleKey(ch);
            count = 0;
        }
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
    if (except == EXCEPTION_NO_SUCH_TASK) echo("TaskManager: no such task");
    if (except == EXCEPTION_NO_SUCH_COMMAND) echo("TaskManager: command not found");
    if (except == EXCEPTION_TASK_EXIST) echo("TaskManager: add task failed. task exists");
    if (except == EXCEPTION_ILLEGAL_EXPRESSION) echo("TaskManager: illegal expression");
    if (except == EXCEPTION_NO_SUCH_COMMAND) echo("TaskManager: illegal expression");
    if (except == EXCEPTION_NOT_A_NUMBER) echo("TaskManager: some field requires a number");
    if (except == EXCEPTION_CANCEL) echo("TaskManager: canceled by user");
    if (except == EXCEPTION_UNDO_FAIL) echo("TaskManager: already at oldest change");
    if (except == EXCEPTION_REDO_FAIL) echo("TaskManager: already at newest change");
    if (except == EXCEPTION_HELP) displayManager->showHelp();
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
        prompt.erase(0,y+1);
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
