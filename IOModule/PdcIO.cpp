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
  return true;
}

void PdcIO::setCommand(CommandList cl){
    commandReady = true;
    commandList = cl;
}

void PdcIO::echo(string s){
    displayManager->echo(s);    
}
