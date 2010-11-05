#include "ListDisplayElement.h"
#include "../../filters/KFilter.h"
ListDisplayElement::ListDisplayElement(TaskList* taskList, Parser* pser,DisplayManager* dm){
    parser = pser;
    displayManager = dm;
    detailList.clear();
    lastSelectedSn = 0;
    originalList = NULL;
    list = taskList;
    navigateRow = 0;
    selectTask = 0;
    int mx=0, my=0;
    getmaxyx(stdscr, mx, my);
    int height = mx - 6;
    int width = my;
    int startx = 5;
    int starty = 0;
    listWindow = create_newwin(height, width, startx, starty); 
    //draw(); 
    wattron(listWindow, _NORMAL);
}
ListDisplayElement::~ListDisplayElement(){
    wattroff(listWindow, _NORMAL);
    destroy_win(listWindow);
    delete list;
    if (originalList != list) delete originalList;
};

void ListDisplayElement::draw(){
    int mx=0, my=0;
    getmaxyx(listWindow, mx, my);
    vector<sortKeyword_e> keys;
    keys.push_back(DEADLINE);
    Comparer* cmp = new Comparer(keys);
    tasks = list->sort(cmp);
    delete cmp;
    if (detailList.empty() )
        for (int i=0; i<tasks.size(); i++) detailList[tasks[i]->getSerialNumber()] = false; 
    if (selectTask >= tasks.size()) selectTask = tasks.size()-1;
    reconstructLines();
    if (navigateRow >= lines.size() && lines.size()>0) navigateRow = lines.size()-1;
    werase(listWindow);
    wborder(listWindow, '|', '|', '-','-','+','+','+','+');
/*    string s = parser -> resultToOutput(new Result(list,false));
    wprintw(listWindow, s.c_str());   */ 
    for (int i=navigateRow;i<lines.size()&&i<navigateRow+mx-2;i++){
        wmove(listWindow,i+1-navigateRow,1);
        if (i >= taskStartAt[selectTask]) wattron(listWindow,_SELECT);
        if (selectTask != tasks.size()-1 && i >= taskFinishAt[selectTask]){
            wattroff(listWindow,_SELECT);
            wattron(listWindow,_NORMAL);
        }
        if (is_time(lines[i])) wattron(listWindow,_TIMELINE);
        wprintw(listWindow,lines[i].c_str());
        if (is_time(lines[i])) wattroff(listWindow,_TIMELINE);
    }
    wattroff(listWindow,_SELECT);
    wattron(listWindow,_NORMAL);
    wrefresh(listWindow);
    drawSelectNumber();
    move(0,my-1);
}
void ListDisplayElement::naiveDraw(){
    if (navigateRow >= lines.size() && lines.size()>0) navigateRow = lines.size()-1;
    int mx=0, my=0;
    getmaxyx(listWindow, mx, my);
    reconstructLines();
    werase(listWindow);
    wborder(listWindow, '|', '|', '-','-','+','+','+','+');
/*    string s = parser -> resultToOutput(new Result(list,false));
    wprintw(listWindow, s.c_str());   */ 
    for (int i=navigateRow;i<lines.size()&&i<navigateRow+mx-2;i++){
        wmove(listWindow,i+1-navigateRow,1);
        if (i >= taskStartAt[selectTask]) wattron(listWindow,_SELECT);
        if (selectTask != tasks.size()-1 && i >= taskFinishAt[selectTask]){
            wattroff(listWindow,_SELECT);
            wattron(listWindow,_NORMAL);
        }
        if (is_time(lines[i])) wattron(listWindow,_TIMELINE);
        wprintw(listWindow,lines[i].c_str());
        if (is_time(lines[i])) wattroff(listWindow,_TIMELINE);
    }
    wattroff(listWindow,_SELECT);
    wattron(listWindow,_NORMAL);
    wrefresh(listWindow);
    drawSelectNumber();
    move(0,my-1);
}
void ListDisplayElement::handleKey(int ch){
    int mx,my;
    getmaxyx(listWindow,mx,my);
    string st;
    CommandList cl;
    string newGrp,newDetail,newTime,newPri;
    vector<string> editDetail;
    int newTaskSerial;
    switch (ch){
        case (int)'U':
            displayManager->setCommand(parser->inputToCommandList("undo"));
            break;
        case (int)'R':
            displayManager->setCommand(parser->inputToCommandList("redo"));
            break;
        case (int)'c':
            selectByCalendar();
            break;
        case (int)'f':
            if (tasks.size() != 0){
                st = "finish " + NumberToString(tasks[selectTask]->getSerialNumber());
                cl = parser->inputToCommandList(st);
                displayManager->setCommand(cl);
            }
            break;
        case (int)'d':
            if (tasks.size() != 0){
                st = "rm " + NumberToString(tasks[selectTask]->getSerialNumber());
                cl = parser->inputToCommandList(st);
                displayManager->setCommand(cl);
                if (list != originalList) list->removeTask(tasks[selectTask]->getSerialNumber());
                if (selectTask+1 < tasks.size()) selectTask++;
                else if (selectTask-1 >= 0 ) selectTask--;
            }
            break;
        case (int)'p':
            if (navigateRow > 0) navigateRow--;
            naiveDraw();
            break;
        case (int)'n':
            if (navigateRow+1 < lines.size()) navigateRow++;
            naiveDraw();
            break;
        case (int)'e':
            editDetail = editSelect();
            if (tasks.size()!=0){
                newGrp = editDetail[0];
                newTime = editDetail[1];
                newPri = editDetail[2];
                newDetail = editDetail[3];
                displayManager->setCommand(parser->inputToCommandList("edit "+NumberToString(tasks[selectTask]->getSerialNumber())+" -d \""+newDetail+"\""+" -g \""+newGrp+"\" -t " + newTime + " -p " + newPri));
            }
            break;
        case (int)'a':
            if (list!=originalList) break;
            newTaskSerial = originalList->getSerial()+1;
            tasks.push_back(new Task(NO_SPECIFIC_DEADLINE, 0, "", 0, false,newTaskSerial, "default"));
            selectTask = tasks.size()-1;
            showDetail();
            naiveDraw();
            editDetail = editSelect();
            newGrp = editDetail[0];
            newTime = editDetail[1];
            newPri = editDetail[2];
            newDetail = editDetail[3];
            lastSelectedSn = tasks[selectTask] -> getSerialNumber();
            lastNavigateToSelect = taskStartAt[selectTask] - navigateRow;
            selectTask = 100000000;
            delete tasks[tasks.size()-1];
            displayManager->setCommand(parser->inputToCommandList("add -d \""+newDetail+"\""+" -g \""+newGrp+"\" -t " + newTime + " -p " + newPri));
            break;
        case (int)'s':
            search();
            break;
        case KEY_UP:
        case 'k':
            if (selectTask > 0) selectTask--;
            if (selectTask >= 0 && selectTask < tasks.size() && taskStartAt[selectTask]<navigateRow) navigateRow = taskStartAt[selectTask];
            if (selectTask >= 0 && selectTask < tasks.size() && taskFinishAt[selectTask]>navigateRow+mx-2) navigateRow = taskFinishAt[selectTask]-mx+2;
            if (navigateRow !=0 && is_time(lines[navigateRow - 1])) navigateRow--;
            naiveDraw();
            break;
        case 'G':
            selectTask = tasks.size() - 1;
        case KEY_DOWN:
        case 'j':
            if (selectTask+1 < tasks.size()) selectTask++;
            if (selectTask >= 0 && selectTask < tasks.size() && taskStartAt[selectTask]<navigateRow) navigateRow = taskStartAt[selectTask];
            if (selectTask >= 0 && selectTask < tasks.size() && taskFinishAt[selectTask]>navigateRow+mx-2) navigateRow = taskFinishAt[selectTask]-mx+2;
            naiveDraw();
            break;
        case (int)' ':
        case 10:
        case 13:
            if (tasks.size()!=0){
                if (detailList[tasks[selectTask] -> getSerialNumber()]) hideDetail();
                else showDetail();
            }
            break;
        default:
            break;
    }
    if (selectTask < tasks.size()){
        lastSelectedSn = tasks[selectTask] -> getSerialNumber();
        lastNavigateToSelect = taskStartAt[selectTask] - navigateRow;
    }
}
void ListDisplayElement::handleConfirm(bool flag){
}
void ListDisplayElement::handleResult(Result* result){
    if (! result->isNull){
        delete list;
        if (originalList != list) delete originalList;
        list = result;
        originalList = result;
        draw();
    }else{
        delete result;
        displayManager->setCommand(parser->inputToCommandList("ls"));
    }
}
string ListDisplayElement::formatDate(time_t t){
    string months[]  = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
    };
    string st;
    if (t==NO_SPECIFIC_DEADLINE) st = "< Anytime >  "; 
    else{
        struct tm* datetime = localtime(&t);
        st = "< "+ NumberToString(datetime->tm_mday)+" "+months[datetime->tm_mon]+" "+NumberToString(datetime->tm_year+1900)+" >  ";
        time_t curTime = currentTime();
        datetime = localtime(&curTime);
        datetime->tm_hour = 0;
        datetime->tm_min = 0;
        datetime->tm_sec = 0;
        curTime = mktime(datetime); 
        if (t>= curTime && t< curTime+24*60*60) st =  "< ---- Today ---- >  ";
        if (t>= curTime+24*60*60 && t< curTime+48*60*60) st =  "< -- Tomorrow --- >  ";
        if (t>= curTime-24*60*60 && t< curTime) st =  "< -- Yesterday -- >  "; 
    }
    int mx,my;
    getmaxyx(stdscr,mx,my);
    st = string((my-2-st.length()),' ') + st; 
//    while (st.length()+13<my) st = " "+st;
//    while (st.length()+3<my) st = " "+st;
    return st;
}
void ListDisplayElement::reconstructLines(){
    int mx=0, my=0;
    getmaxyx(stdscr, mx, my);
   
    lines.clear();
    taskStartAt.clear(); 
    taskFinishAt.clear(); 
    string lastTime = "";
    for (int i=0; i<tasks.size(); i++){
        string newTime = formatDate(tasks[i]->getDeadline());
        if (newTime != lastTime){
              lastTime = newTime;
            lines.push_back(newTime);
        }
        taskStartAt.push_back(lines.size());
        if (! detailList[tasks[i] -> getSerialNumber()] ){
            lines.push_back("   ");
            string temps;
            temps = NumberToString(tasks[i]->getSerialNumber());
            lines[lines.size() - 1].append(temps);
            while (lines[lines.size() - 1].size() < 8) lines[lines.size() - 1].push_back(' ');
            if (tasks[i]->getIsFinished()) lines[lines.size() - 1].append("f ");
            else lines[lines.size() - 1].append("  ");         
            temps = tasks[i]->getGroup();
            while (temps.length()<9) temps.push_back(' ');
            if (temps.length()>9) temps = temps.substr(0,9);
            temps.push_back(' ');
            lines[lines.size() - 1].append(temps);
            temps = tasks[i]->getDescription();
            int mlength = my - 5 - 10 - 10;
            if (temps.length() > mlength) 
                temps = temps.substr(0,mlength-3) + "...";
            lines[lines.size() - 1].append(temps);
        }else{
            lines.push_back("   ");
            string temps;
            temps = NumberToString(tasks[i]->getSerialNumber());
            lines[lines.size() - 1].append(temps);
            while (lines[lines.size() - 1].size() < 8) lines[lines.size() - 1].push_back(' ');
            string grp = tasks[i]->getGroup();
            int firstHalf = 5;//(my-16-grp.size())/2;
            lines[lines.size() - 1] += string(firstHalf,'-');
            lines[lines.size() - 1] += grp;
            lines[lines.size() - 1] += string(my-16-firstHalf-grp.size(),'-');

            lines.push_back("");
            lines[lines.size() -1] = "             Number:     ";
            temps = NumberToString(tasks[i]->getSerialNumber());
            lines[lines.size() -1].append(temps);
            while (lines[lines.size() - 1].size() < 33) lines[lines.size() - 1].push_back(' ');
            lines[lines.size() -1].append("Deadline:     ");
            lines[lines.size() -1].append(formatTime(tasks[i]->getDeadline()).substr(0,24) );

            lines.push_back("");
            lines[lines.size() -1] = "           Priority:     ";
            temps = NumberToString(tasks[i]->getPriority());
            lines[lines.size() -1].append(temps);
            while (lines[lines.size() - 1].size() < 33) lines[lines.size() - 1].push_back(' ');
            lines[lines.size() -1].append("  Status:     ");
            lines[lines.size() -1].append(tasks[i]->getIsFinished()?"Finished":"Doing");

	        lines.push_back("            Details:");
	        temps = tasks[i]->getDescription();
            int lengthLimit = my-27;
            bool flag = true;
            while (temps != ""||flag){
                flag = false;
                lines.push_back("               "+temps.substr(0,lengthLimit));
                if (lengthLimit >= temps.size()) temps = "";
                else temps = temps.substr(lengthLimit,temps.size());
            }
            lines.push_back("        "+string(my-16,'-'));
        }
        taskFinishAt.push_back(lines.size());
    }
    taskStartAt.push_back(lines.size());
    for (int i=0;i<lines.size();i++){
        while (lines[i].length() < my-2) lines[i].push_back(' ');
    }
}

void ListDisplayElement::refreshEditArea(WINDOW* win, int row0, int row1, int col0, int col1, string newStr, int startPos,int* cR, int* cC, string completion,int curPos){
    int tmp = startPos;
    int curRow = row0,curCol = col0;
    string ss = newStr.substr(0,curPos)+completion+newStr.substr(curPos,newStr.length() - curPos);
//    string ss = newStr + " :"+NumberToString(curPos);//completion;
    for (int i=row0;i<=row1;i++)
        for (int j=col0;j<=col1;j++){
            if (tmp == newStr.size()) {curRow = i; curCol = j; if (tmp == ss.size()) tmp++;}
            move(i,j);
            if (tmp == curPos){
                attroff(_EDIT);
                attron(_BOLD);
            }
            if (tmp == curPos+completion.size()) {
                attroff(_BOLD);
                attron(_EDIT);
            }
            addch(tmp<ss.size()?ss[tmp++]:' ');
        }
    attroff(_BOLD);
    attron(_EDIT);
    move(curRow,curCol);
    *cR = curRow;
    *cC = curCol;
}
string ListDisplayElement::editArea(WINDOW* win,int row0,int row1,int col0,int col1,string st0,bool numOnly){
    attron(_EDIT);
    row0+=win->_begy+1;
    row1+=win->_begy+1;
    col0+=win->_begx+1;
    col1+=win->_begx+1;
    curs_set(1);
    string newStr = st0;
    int startPos = 0;
    int msize = (row1 - row0 + 1) * (col1 - col0 + 1);
//    if (newStr.size()>=msize) startPos = newStr.size() - msize + 1;
    int curPos = newStr.size()>(col1-col0+1)*(row1-row0+1)?(col1-col0+1)*(row1-row0+1):newStr.size();
    int curRow,curCol;
    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&curRow,&curCol,lastTokenComp(newStr,curPos),curPos);
    bool flag = false;
    int tmp;
    int chLast = 0;
    time_t tLast,tNow;
    while (!flag){
        time(&tLast);
        int ch = getch();
        time(&tNow);
        string comp;
        switch (ch){
            case 10:
            case 13:
                chLast = ch;
                flag= true;
                break;
            case KEY_LEFT:
                chLast = ch;
                if (curPos!=0 && !(curRow == row0 && curCol == col0)){
                    if (curCol == col0){ curCol = col1; curRow--;}
                    else curCol--;
                    curPos--;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,"",curPos);
                    move(curRow,curCol);
                }else if (curRow == row0 && curCol == col0 && !startPos ==0){
                    startPos-=col1-col0+1;
                    curPos--;
                    curCol = col1;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,"",curPos);
                    move(curRow,curCol);
                }
                break;
            case KEY_RIGHT:
                chLast = ch;
                if (curPos!=newStr.size() && !(curRow == row1 && curCol == col1)){
                    if (curCol == col1){ curCol = col0; curRow++;}
                    else curCol++;
                    curPos++;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,"",curPos);
                    move(curRow,curCol);
                }else if (curRow == row1 && curCol == col1 && curPos<newStr.size()){
                    startPos+=col1-col0+1;
                    curPos++;
                    curCol = col0;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,"",curPos);
                    move(curRow,curCol);
                }
                break;
            case KEY_UP:
                chLast = ch;
                if (curPos - (col1-col0+1) >=0 && curRow!=row0){
                    curRow--;
                    curPos-=col1-col0+1;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,"",curPos);
                    move(curRow,curCol);
                }else if( curRow == row0 && startPos>0){
                    tmp = curPos - startPos;
                    startPos = startPos - (col1-col0+1) >0? startPos - (col1-col0+1) : 0;
                    curPos = startPos+tmp;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,"",curPos);
                    move(curRow,curCol);
                }
                break;
            case KEY_DOWN:
                chLast = ch;
                if (curPos + col1-col0+1 <= newStr.size() && curRow!=row1){
                    curRow++;
                    curPos+=col1-col0+1;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,"",curPos);
                    move(curRow,curCol);
                }else if(curRow == row1 && newStr.size()-startPos >= msize){
                    tmp = curPos - startPos;
                    startPos = startPos + (col1-col0+1);// > msize - newStr.size()+1? startPos - (col1-col0+1) : msize - newStr.size() +1;
                    curPos = startPos+tmp;
                    if (curPos > newStr.size()){
                        tmp = curPos - newStr.size();
                        curPos = newStr.size();
                        curCol -= tmp;
                    }
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,"",curPos);
                    move(curRow,curCol);
                }
                break;
            case KEY_BACKSPACE:
            case 8:
            case 127:
                chLast = ch;
                if (!(curCol == col0 && curRow == row0) && curPos != 0){
                    newStr.erase(curPos - 1,1);
                    if (curCol == col0){ curCol = col1; curRow--;}
                    else curCol--;
                    curPos--;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,lastTokenComp(newStr,curPos),curPos);
                    move(curRow,curCol);
                }else if (curPos !=0){
                    startPos -= col1-col0+1;
                    newStr.erase(curPos - 1,1);
//                    startPos--;
                    curPos--;
                    curCol = col1;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,lastTokenComp(newStr,curPos),curPos);
                    move(curRow,curCol);
                }
                break;
            case KEY_ESC:
            case 3:
                chLast = ch;
                newStr = st0;
                curRow = row0, curCol = col0;
                curPos = st0.size();
                tmp = 0;
                for (int i=row0;i<=row1;i++)
                    for (int j=col0;j<=col1;j++){
                        if (tmp == newStr.size()) {curRow = i; curCol = j;}
                         move(i,j);
                         addch(tmp<newStr.size()?newStr[tmp++]:' ');
                    }
                flag = true;
                break;
            case '\t':
                chLast = ch;
                //bug here , fix later
                //end of a line problem | not typing but press tab 
                comp = lastTokenComp(newStr, curPos);
                newStr = newStr.substr(0,curPos) + comp + newStr.substr(curPos,newStr.size()-curPos);
                curPos += comp.size();
                refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,"",curPos);
                curCol += comp.size();
                move(curRow,curCol);
                break;
            case 'j':
                if (chLast == 'j' && tLast >= tNow-1 && !numOnly){
                    newStr[curPos-1] = '"';
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,lastTokenComp(newStr,curPos),curPos);
                    move(curRow,curCol);
                    chLast = 0;
                    break;
                }
                chLast = 'j';
            case ' ':
                if (chLast == ' ' && tLast >= tNow-1){
                    if (!numOnly)
                        if (!(curCol == col0 && curRow == row0) && curPos != 0){
                            newStr.erase(curPos - 1,1);
                            if (curCol == col0){ curCol = col1; curRow--;}
                            else curCol--;
                            curPos--;
                            refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,lastTokenComp(newStr,curPos),curPos);
                            move(curRow,curCol);
                        }else if (curPos !=0){
                            startPos -= col1-col0+1;
                            newStr.erase(curPos - 1,1);
        //                    startPos--;
                            curPos--;
                            curCol = col1;
                            refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,lastTokenComp(newStr,curPos),curPos);
                            move(curRow,curCol);
                        }
                    flag = true;
                    break;
                }
            default:
                chLast = ch;
                if (!numOnly || isDigit(ch))
                    if (curCol < col1){//curPos - startPos + 1<msize){
                        newStr.insert(curPos,(char*)&ch,1);
                        curPos++;
                        refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,lastTokenComp(newStr,curPos),curPos);
                        curCol++;
                        move(curRow,curCol);
                    }else{
                        newStr.insert(curPos,(char*)&ch,1);
                        startPos+=col1-col0+1;
                        curPos++;
                        curCol = col0;
                        refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp,lastTokenComp(newStr,curPos),curPos);
                    }
                break;
        }
    }
    curs_set(0);
    attroff(_EDIT);
    attron(_EDITTED);
    curRow = row0, curCol = col0;
    tmp = 0;
    for (int i=row0;i<=row1;i++)
        for (int j=col0;j<=col1;j++){
            if (tmp == newStr.size()) {curRow = i; curCol = j;}
             move(i,j);
             addch(tmp<newStr.size()?newStr[tmp++]:' ');
        }
    attroff(_EDITTED);
    attron(_NORMAL);
    curRow = row0, curCol = col0;
    move(row0,col0);
    return newStr;
}
vector<string> ListDisplayElement::editSelect(){
    //detailList[selectTask] = true;
    //naiveDraw();
    showDetail();
    int mx=0, my=0;
    getmaxyx(listWindow, mx, my);
    string newGrp = editArea(listWindow,taskStartAt[selectTask] - navigateRow,taskStartAt[selectTask] - navigateRow,13,max(23,13+(tasks[selectTask]->getGroup()).size()),tasks[selectTask]->getGroup(),false);
    move(taskStartAt[selectTask] - navigateRow + 3, 1);
    attron(_SELECT);
    printw("%s",lineWithNewGroup(selectTask,newGrp).c_str());
    attroff(_SELECT);
    attron(_NORMAL);
    int theRow = taskStartAt[selectTask]- navigateRow + listWindow->_begy;
    if (theRow + 12 >= mx+listWindow->_begy) theRow= mx+listWindow->_begy-13;
    time_t tt = tasks[selectTask]->getDeadline();
    if (tt != NO_SPECIFIC_DEADLINE){
        struct tm* dd = localtime(&tt);
        dd->tm_hour =0;
        dd->tm_sec =0;
        dd->tm_min =0;
        tt = mktime(dd);
    }
    int newTime = datePicker(tt,theRow,45);//editArea(listWindow,taskStartAt[selectTask]+1- navigateRow,taskStartAt[selectTask]+1- navigateRow,47,71,formatTime(tasks[selectTask]->getDeadline()).substr(0,24));
    naiveDraw();
    move(taskStartAt[selectTask]+1- navigateRow + listWindow->_begy+1,48);
    attron(_EDITTED);
    string times = (formatTime(newTime)).substr(0,24);
    while (times.size()<24) times.push_back(' ');
    printw(times.c_str());
    attroff(_EDITTED);
    move(taskStartAt[selectTask] - navigateRow +listWindow->_begy+1,14);
    attron(_SELECT);
    printw("%s------------------",newGrp.c_str());
    attroff(_SELECT);
    attron(_NORMAL);
    string newPri = editArea(listWindow,taskStartAt[selectTask]+2- navigateRow,taskStartAt[selectTask]+2- navigateRow,25,27,NumberToString(tasks[selectTask]->getPriority()),true);
    string newDetail = editArea(listWindow,taskStartAt[selectTask]+4- navigateRow,taskFinishAt[selectTask] -2- navigateRow,15,my-13,tasks[selectTask]->getDescription(),false);
    //displayManager->setCommand(parser->inputToCommandList("edit "+NumberToString(tasks[selectTask]->getSerialNumber())+" -d \""+newDetail+"\""+" -g \""+newGrp+"\" -t " + newTime + " -p " + newPri));
    newGrp = handleQuo(newGrp);
    newDetail = handleQuo(newDetail);
    vector<string> ans;
    ans.push_back(newGrp);
    ans.push_back(NumberToString(newTime));
    ans.push_back(newPri);
    ans.push_back(newDetail);
    return ans;
}
void ListDisplayElement::showDetail(){
    int mx,my;
    getmaxyx(listWindow,mx,my);
    if (tasks.size()!=0){
//        if (detailList[selectTask]) detailList[selectTask] = false;
        detailList[tasks[selectTask]->getSerialNumber()] = true;
        reconstructLines();
        if (detailList[tasks[selectTask]->getSerialNumber()]){
            if (selectTask >= 0 && selectTask < tasks.size() && taskStartAt[selectTask]<navigateRow) navigateRow = taskStartAt[selectTask];
            if (selectTask >= 0 && selectTask < tasks.size() && taskFinishAt[selectTask]>navigateRow+mx-2) navigateRow = taskFinishAt[selectTask]-mx+2;
        }
        naiveDraw();
    }
}
void ListDisplayElement::hideDetail(){
    int mx,my;
    getmaxyx(stdscr,mx,my);
    if (tasks.size()!=0){
//        if (detailList[selectTask]) detailList[selectTask] = false;
        detailList[tasks[selectTask]->getSerialNumber()] = false;
        naiveDraw();
    }
}

void ListDisplayElement::reset(){
    displayManager->setCommand(parser->inputToCommandList("ls"));
}

void ListDisplayElement::search(){
    if (list != originalList) delete list;
    list = originalList;
    bool flag = false;
    string keyInSt = "";
    searchKeyword = "";
    displayManager->echo("Search: "+searchKeyword);
    int chLast = 0;
    time_t timeLast;
    time_t timeNow;
    TaskList* tmpList;
    while (!flag){
        selectTask = 0;
        time(&timeLast);
        int ch = getch();
        time(&timeNow);
        Filter* kfil;
        switch (ch){
            case KEY_ESC:
            case 3:
                chLast = ch;
                reset();
                draw();
                flag =true;
                break;
            case 10:
            case 13:
                chLast = ch;
                if (tasks.size() == 0) {
                    if (list != originalList) delete list;
                    list = originalList;
                    draw();
                }
                flag = true;
                break;
            case KEY_BACKSPACE:
            case 8:
            case 127:
                chLast = ch;
                if (searchKeyword.size()!=0) searchKeyword = searchKeyword.substr(0,searchKeyword.size() - 1);
                if (keyInSt.size()!=0) keyInSt = keyInSt.substr(0,keyInSt.size() - 1);
//                reset();
                if (list != originalList) delete list;
                list = originalList;              
                displayManager->echo("Search: "+keyInSt);
                kfil = new KFilter("*"+searchKeyword+"*");
                list = list -> getTasks(kfil);
                delete kfil;
                draw(); 
                break;
            case ' ':
                if (chLast == ' ' && timeNow <= timeLast+1){
                    flag = true;
                    if (tasks.size() == 0) {
                        if (list != originalList) delete list;
                        list = originalList;
                        draw();
                    }
                    break;
                }
            default:
                chLast = ch;
                keyInSt.push_back((char)ch);
                if (ch == (int)' ') ch = (int)'*';
                searchKeyword.push_back((char)ch);
                displayManager->echo("Search: "+keyInSt);
                kfil = new KFilter("*"+searchKeyword+"*");
                tmpList = list -> getTasks(kfil);
                delete kfil;
                if (list != originalList) delete list;
                list = tmpList;
                draw(); 
                break;
        }
    }
    displayManager->echo("Search finish");
}
void ListDisplayElement::restoreLastView(){
    selectTask = 0;
    for (int i=0;i<tasks.size();i++){
        if (lastSelectedSn == tasks[i]->getSerialNumber()) {
            selectTask = i;
            navigateRow = taskStartAt[selectTask] - lastNavigateToSelect;
            if (navigateRow < 0) navigateRow = 0;
            break;
        }
    }
    naiveDraw();
}
void ListDisplayElement::resize(int row0){
    destroy_win(listWindow);
    int mx=0, my=0;
    getmaxyx(stdscr, mx, my);
    int height = mx - row0 -1;
    int width = my;
    int startx = row0;
    int starty = 0;
    listWindow = create_newwin(height, width, startx, starty);  
}

void ListDisplayElement::drawCalendar(time_t theTime,int startRow, int startCol){
    string months[]  = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
    };
    time_t curTime = theTime;
    struct tm* curDate = localtime(&curTime);
    int curMon = curDate->tm_mon;
    int curDay = curDate->tm_mday;
    int curYear = curDate->tm_year + 1900;
    time_t startTime = curTime;
    struct tm* datetime = localtime(&startTime);
    while (datetime->tm_wday!=0 || (datetime->tm_mon == curMon && datetime->tm_mday > 1)){
        startTime -= 24*60*60;
        datetime = localtime(&startTime);
    }
//    int startCol = 0;
 //   int startRow = 0;
    int curCol = startCol;
    int curRow = startRow+1;
    move(curRow,startCol);
//    printw("%34s"," ");
    curRow++;
    move(curRow,startCol);
    attron(_REVERSE);
    printw("%15s %4d              ",months[curMon].c_str(),curYear);
    attroff(_REVERSE);
    attron(_NORMAL);
    curRow++;
    move(curRow,startCol);
    attron(_UNDERLINE); 
    printw("  Week  | Su Mo Tu We Th Fr Sa    ");
    attroff(_UNDERLINE);
    attron(_NORMAL);
    curRow++;
    vector<sortKeyword_e> keys;
    keys.push_back(DEADLINE);
    Filter* ifil = new IFilter(startTime,startTime+42*24*60*60);
    Comparer* cmp = new Comparer(keys);
    TaskList* tmpTL = originalList->getTasks(ifil);
    vector<Task*> thetasks = (tmpTL)->sort(cmp);
    delete cmp;
    delete ifil;
    int taskNum = 0; 
    for (int i=0;i<6;i++){
        datetime = localtime(&startTime);
        int numOfWeek = (datetime->tm_yday)/7 + 1;
        move(curRow,startCol);
        printw("  %4d  |",numOfWeek);
        curCol += 9;
        for (int j=0;j<7;j++){
            move(curRow,curCol);
            datetime = localtime(&startTime);
            if (datetime->tm_mon == curMon) attron(_BOLD);
            if (datetime->tm_mday == curDay && datetime->tm_mon == curMon) attron(_REVERSE);
            while (taskNum<thetasks.size() && thetasks[taskNum]->getDeadline()<startTime) taskNum++;
            if (taskNum<thetasks.size() && thetasks[taskNum]->getDeadline()<startTime+24*60*60)
                attron(_TASKDAY);
            printw("%3d",datetime->tm_mday);
            if (taskNum<thetasks.size() && thetasks[taskNum]->getDeadline()<startTime+24*60*60){
                attroff(_TASKDAY);
                attron(_NORMAL);
            }
            if (datetime->tm_mday == curDay && datetime->tm_mon == curMon) {
                attroff(_REVERSE);
                attron(_NORMAL);
            }
            if (datetime->tm_mon == curMon) {
                attroff(_BOLD);
                attron(_NORMAL);
            }
            startTime += 24*60*60;
            curCol+=3;
        }
        move(curRow,curCol);
        printw("    ");
        curRow+=1;
        curCol=startCol;
    }
    delete tmpTL;
    move(curRow,startCol);
    printw("%34s"," ");
    curRow++;
    refresh();
}

time_t ListDisplayElement::datePicker(time_t curTime,int startRow, int startCol){

//    time_t curTime = currentTime();
    if (curTime == NO_SPECIFIC_DEADLINE) {
        curTime = currentTime();
        struct tm* dd = localtime(&curTime);
        dd->tm_hour =0;
        dd->tm_sec =0;
        dd->tm_min =0;
        curTime= mktime(dd);
    }
    drawCalendar(curTime,startRow,startCol);
    bool flag = false;

    int count = 0;
    while (!flag){
        int ch = getch();
        if (ch >= 48 && ch < 58) count = count * 10 + ch - 48;
        switch (ch){
            case KEY_ESC:
            case 3:
            case 'q':
                curTime = NO_SPECIFIC_DEADLINE;
            case 10:
            case 13:
            case ' ':
                flag = true;
                break;
            case KEY_LEFT:
            case 'h':
                if (count ==0) count = 1;
                for (int i=0;i<count;i++)
                    curTime -= 24*60*60;
                count = 0;
                break;
            case KEY_RIGHT:
            case 'l':
                if (count ==0) count = 1;
                for (int i=0;i<count;i++)
                    curTime += 24*60*60;
                count = 0;
                break;
            case KEY_UP:
            case 'k':
                if (count ==0) count = 1;
                for (int i=0;i<count;i++)
                    curTime -= 7 * 24*60*60;
                count = 0;
                break;
            case KEY_DOWN:
            case 'j':
                if (count ==0) count = 1;
                for (int i=0;i<count;i++)
                    curTime += 7 * 24*60*60;
                count = 0;
                break;
            default:
                break;
        }
        drawCalendar(curTime,startRow,startCol);
    }
    //naiveDraw();

    struct tm* datetime = localtime(&curTime);   
    int year = datetime->tm_year + 1900;
    int mon = datetime->tm_mon;
    int day = datetime->tm_mday;
    int limit[] = {24,60,60};
    int hourMinSec[3];
    hourMinSec[0] = datetime->tm_hour;
    hourMinSec[1] = datetime->tm_min;
    hourMinSec[2] = 0;
    int curFoc = 0;
    drawTime(year,mon,day,hourMinSec,curFoc,startRow,startCol);
    if (curTime != NO_SPECIFIC_DEADLINE) flag = false;
//    count = 0;
    while (!flag){
        int ch = getch();
        if (ch >= 48 && ch < 58){
          //  count = count * 10 + ch - 48;
          hourMinSec[curFoc] = (hourMinSec[curFoc]*10+ch-48)%100;
        }
        switch (ch){
            case KEY_ESC:
            case 3:
            case 'q':
                curTime = NO_SPECIFIC_DEADLINE;
            case 10:
            case 13:
            case ' ':
                if (hourMinSec[curFoc] >= limit[curFoc]) hourMinSec[curFoc] = limit[curFoc] - 1;
                flag = true;
                break;
            case KEY_LEFT:
            case 'h':
            //    if (count == 0) count = 1;
             //   for (int i=0;i<count;i++)
                    if (hourMinSec[curFoc] >= limit[curFoc]) hourMinSec[curFoc] = limit[curFoc] - 1;
                    if (curFoc!=0) curFoc--;
              //  count = 0;
                break;
            case KEY_RIGHT:
            case 'l':
               // if (count == 0) count = 1;
               // for (int i=0;i<count;i++)
                    if (hourMinSec[curFoc] >= limit[curFoc]) hourMinSec[curFoc] = limit[curFoc] - 1;
                    if (curFoc!=3) curFoc++;
               // count = 0;
                break;
            case KEY_UP:
            case 'k':
                //if (count == 0) count = 1;
                //for (int i=0;i<count;i++)
                    hourMinSec[curFoc] = (hourMinSec[curFoc] + limit[curFoc] - 1) % limit[curFoc]; 
                //count = 0;
                break;
            case KEY_DOWN:
            case 'j':
                //if (count == 0) count = 1;
                //for (int i=0;i<count;i++)
                    hourMinSec[curFoc] = (hourMinSec[curFoc] + limit[curFoc] + 1) % limit[curFoc]; 
                //count = 0;
                break;
            default:
                break;
        }
        drawTime(year,mon,day,hourMinSec,curFoc,startRow,startCol);
    }
    if (curTime != NO_SPECIFIC_DEADLINE){
        datetime = localtime(&curTime);
        datetime->tm_hour = hourMinSec[0]; 
        datetime->tm_min = hourMinSec[1]; 
        datetime->tm_sec = hourMinSec[2]; 
        return mktime(datetime);    
    }else
        return curTime;
}

void ListDisplayElement::drawTime(int year,int mon,int day,int hourMinSec[],int curFoc,int startRow,int startCol){
    string months[]  = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
    };
    int curCol = startCol;
    int curRow = startRow+1;
    move(curRow,startCol);
//    printw("%34s"," ");
    curRow++;
    move(curRow,startCol);
    attron(_REVERSE);
    printw("%13d %3s %4d            ",day,months[mon].c_str(),year);
    attroff(_REVERSE);
    attron(_NORMAL);
    string hour = NumberToString(hourMinSec[0]);
    if (hour.length() < 2) hour = '0'+hour;
    string min = NumberToString(hourMinSec[1]);
    if (min.length() < 2) min = '0'+min;
    string sec = NumberToString(hourMinSec[2]);
    if (sec.length() < 2) sec ='0'+sec;
    for (int i=0;i<8;i++){
        curRow++; 
        move(curRow,startCol);
        printw("%34s"," ");
        if (i==1){
            move(curRow,startCol);
            printw("%10s"," ");
            attron(_UNDERLINE);
            printw("%4s %4s %4s","Hour","Min","Sec");
            attroff(_UNDERLINE);
            attron(_NORMAL);
            printw("%10s"," ");
        }
        if (i==2){
            move(curRow,startCol);
            printw("%10s"," ");
            if (curFoc == 0) attron(_REVERSE);
            printw("%3s",hour.c_str());
            if (curFoc == 0){
                attroff(_REVERSE);
                attron(_NORMAL);
            }
            printw(" :");
            if (curFoc == 1) attron(_REVERSE);
            printw("%3s",min.c_str());
            if (curFoc == 1) {
                attroff(_REVERSE);
                attron(_NORMAL);
            }
            printw(" :");
            if (curFoc == 2) attron(_REVERSE);
            printw("%3s",sec.c_str());
            if (curFoc == 2) {
                attroff(_REVERSE);
                attron(_NORMAL);
            }
            printw("%10s"," ");
        }
    }
    refresh();

}
void ListDisplayElement::drawSelectNumber(){
    string months[]  = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
    };
    time_t now = currentTime();
    struct tm* datetime;
    datetime = localtime(&now);
    string today = "Today is "+NumberToString(datetime->tm_mday)+" "+months[datetime->tm_mon]+" "+NumberToString(datetime->tm_year + 1900);
    string st =" "+ NumberToString((selectTask+1)>tasks.size()?tasks.size():selectTask+1)+" of "+NumberToString(tasks.size())+" Tasks ";
    int mx,my;
    getmaxyx(listWindow,mx,my);
    my -= st.length();
    wmove(listWindow,mx-1,my-2);
    wprintw(listWindow,st.c_str());
    wattron(listWindow,_TIMELINE);
    wmove(listWindow,mx-1,2);
    wprintw(listWindow,today.c_str());
    wattroff(listWindow,_TIMELINE);
    wrefresh(listWindow);
}
string ListDisplayElement::lineWithNewGroup(int i,string group){

    int mx,my;
    getmaxyx(stdscr,mx,my);
    string line = "   ";
    string temps;
    temps = NumberToString(tasks[i]->getSerialNumber());
    line.append(temps);
    while (line.size() < 8) line.push_back(' ');
    string grp = group;
    int firstHalf = 5;//(my-16-grp.size())/2;
    line += string(firstHalf,'-');
    line += grp;
    line += string(my-16-firstHalf-grp.size(),'-');

    return line;
}
bool ListDisplayElement::is_time(string st){
    int l = st.size();
    return (st[l-1] == ' ' && st[l-2] == ' '&& st[l-3] == '>' && st[l-4] == ' ');// && st[l-9] == ' ' && st[l-13] == ' ');
}
void ListDisplayElement::selectByCalendar(){
    time_t curTime = currentTime();
    struct tm* datetime = localtime(&curTime);
    datetime->tm_hour = 0;
    datetime->tm_min = 0;
    datetime->tm_sec = 0;
    curTime = mktime(datetime);
    
    int mx,my;
    getmaxyx(stdscr,mx,my);

    int startCol = my-1-34;
    int startRow = mx-1-12;

    Filter* ifil = new IFilter(curTime,curTime+24*60*60);
    if (list != originalList) delete list;
    list = originalList->getTasks(ifil);
    delete ifil;
    draw();
    drawCalendar(curTime,startRow,startCol);
    bool flag = false;

    int count = 0;
    while (!flag){
        bool escFlag = false;
        int ch = getch();
        if (ch >= 48 && ch < 58) count = count * 10 + ch - 48;
        switch (ch){
            case 10:
            case 13:
            case ' ':
                if (tasks.size() == 0) escFlag = true;
                flag = true;
                break;
            case KEY_ESC:
            case 3:
            case 'q':
                escFlag = true;
                flag = true;
                break;
            case KEY_LEFT:
            case 'h':
                if (count ==0) count = 1;
                for (int i=0;i<count;i++)
                    curTime -= 24*60*60;
                count = 0;
                break;
            case KEY_RIGHT:
            case 'l':
                if (count ==0) count = 1;
                for (int i=0;i<count;i++)
                    curTime += 24*60*60;
                count = 0;
                break;
            case KEY_UP:
            case 'k':
                if (count ==0) count = 1;
                for (int i=0;i<count;i++)
                    curTime -= 7 * 24*60*60;
                count = 0;
                break;
            case KEY_DOWN:
            case 'j':
                if (count ==0) count = 1;
                for (int i=0;i<count;i++)
                    curTime += 7 * 24*60*60;
                count = 0;
                break;
            default:
                break;
        }
        ifil = new IFilter(curTime,curTime+24*60*60);
        if (list != originalList) delete list;
        if (!escFlag)
            list = originalList->getTasks(ifil);
        else list = originalList;
        delete ifil;
        draw();
        drawCalendar(curTime,startRow,startCol);
    }

    naiveDraw();

}

string ListDisplayElement::handleQuo(string s0){
    string ss = "";
    for (int i=0;i<s0.length();i++){
        if (s0[i] == '\\'){
            ss.push_back('\\');
            ss.push_back('\\');
        }else if (s0[i] == '"'){
            ss.push_back('\\');
            ss.push_back('"');
        }else ss.push_back(s0[i]);
    }
    return ss;
}

string ListDisplayElement::lastTokenComp(string st, int pos){
   int pos0 = pos-1;
   int length = 0;
   while (pos0>=0 && st[pos0]!='"' && st[pos0] != ' ' && st[pos0] != '-' && st[pos0] != '|'){
         pos0--; 
         length++;
   }
   string s0 = (length == 0)?"":st.substr(pos0+1,length);
   return (displayManager->agent)->ask(s0);
}
