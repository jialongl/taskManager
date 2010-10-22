#include "PdcIO.h"
#include "TUI/DisplayManager.h"

PdcIO::PdcIO(){
        initscr();
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
    commandReady = false;
    int ch;
    int mx=0, my=0;
/*    
    getmaxyx(stdscr, mx, my);
    move(mx - 1,0);
    printw("> ");
    */
    while (!commandReady){
        ch = getch();
        if (ch == 3)  setCommand(parser->inputToCommandList("exit"));
        else if (ch == (int)'Q') setCommand(parser->inputToCommandList("notui"));
        else displayManager -> handleKey(ch);
    }

    return commandList;
}

void PdcIO::showOutput(Result* result){
  //  printw((parser->resultToOutput(result)).c_str());
  displayManager -> handleResult(result);
//    IOModule->echo("show output!");
}

void PdcIO::showWelcomeMessage(){
//     printw("TaskManager V0.2  TUI with Pdcurses\n");
//     refresh();
}
    
void PdcIO::handleException(exception_e except){
/*				if (except == EXCEPTION_NO_SUCH_TASK) cout<<"TaskManager: no such task"<<endl;
				if (except == EXCEPTION_NO_SUCH_COMMAND) cout<<"TaskManager: command not found"<<endl;
				if (except == EXCEPTION_TASK_EXIST) cout<<"TaskManager: add task failed. task exists"<<endl;
				if (except == EXCEPTION_ILLEGAL_EXPRESSION) cout<<"TaskManager: illegal expression"<<endl;
				if (except == EXCEPTION_HELP) displayHelp();
                */
    }

bool PdcIO::confirm(string prompt){
    /*
        cout<<prompt;
        string keyIn;
        cin>>keyIn;
        if (keyIn == "Yes" || keyIn == "YES" || keyIn == "Y" || keyIn == "y"){
            return true;
        }
        else return false;
        */
    return true;
    }
void PdcIO::setCommand(CommandList cl){
    commandReady = true;
    commandList = cl;
}
void PdcIO::echo(string s){
    displayManager->echo(s);    
}
