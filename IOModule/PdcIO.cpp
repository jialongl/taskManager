
PdcIO::PdcIO(){
        initscr();
        raw();
        keypad(stdscr, TRUE);
        noecho();
    }
PdcIO::~PdcIO(){
        endwin();
    }

CommandList PdcIO::getCommand(){
    int ch;
    string st;
    for (;;){
        ch = getch();
        if (ch == 'Q' || ch == 3)
            return parser->inputToCommandList("exit");
        else if (ch == 13 || ch == 10){
            printw("\n");
            return parser->inputToCommandList(st);
        }else{
            st = st.append(1,(char)ch);
            printw("%c",ch);
            refresh();
        } 
    }
}

void PdcIO::showOutput(Result* result){
    printw((parser->resultToOutput(result)).c_str());
    }

void PdcIO::showWelcomeMessage(){
     printw("TaskManager V0.2  TUI with Pdcurses\n");
     refresh();
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

