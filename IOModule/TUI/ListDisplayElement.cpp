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
}
ListDisplayElement::~ListDisplayElement(){
    destroy_win(listWindow);
};

void ListDisplayElement::draw(){
    int mx=0, my=0;
    getmaxyx(listWindow, mx, my);
    vector<sortKeyword_e> keys;
    keys.push_back(DEADLINE);
    tasks = list->sort(new Comparer(keys));
    if (detailList.empty() )
        for (int i=0; i<tasks.size(); i++) detailList[tasks[i]->getSerialNumber()] = false; 
    if (selectTask >= tasks.size()) selectTask = tasks.size()-1;
    reconstructLines();
    werase(listWindow);
    wborder(listWindow, '|', '|', '-','-','+','+','+','+');
/*    string s = parser -> resultToOutput(new Result(list,false));
    wprintw(listWindow, s.c_str());   */ 
    for (int i=navigateRow;i<lines.size()&&i<navigateRow+mx-2;i++){
        wmove(listWindow,i+1-navigateRow,1);
        if (i >= taskStartAt[selectTask]) wattron(listWindow,A_BOLD);
        if (selectTask != tasks.size()-1 && i >= taskStartAt[selectTask + 1]) wattroff(listWindow,A_BOLD);
        wprintw(listWindow,lines[i].c_str());
    }
    wattroff(listWindow,A_BOLD);
    wrefresh(listWindow);
    move(0,my-1);
}
void ListDisplayElement::naiveDraw(){
    int mx=0, my=0;
    getmaxyx(listWindow, mx, my);
    reconstructLines();
    werase(listWindow);
    wborder(listWindow, '|', '|', '-','-','+','+','+','+');
/*    string s = parser -> resultToOutput(new Result(list,false));
    wprintw(listWindow, s.c_str());   */ 
    for (int i=navigateRow;i<lines.size()&&i<navigateRow+mx-2;i++){
        wmove(listWindow,i+1-navigateRow,1);
        if (i >= taskStartAt[selectTask]) wattron(listWindow,A_BOLD);
        if (selectTask != tasks.size()-1 && i >= taskStartAt[selectTask + 1]) wattroff(listWindow,A_BOLD);
        wprintw(listWindow,lines[i].c_str());
    }
    wattroff(listWindow,A_BOLD);
    wrefresh(listWindow);
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
        case (int)'f':
            if (tasks.size() != 0){
                st = "finish " + NumberToString(tasks[selectTask]->getSerialNumber());
                cl = parser->inputToCommandList(st);
                displayManager->setCommand(cl);
            }
            break;
        case (int)'d':
            if (tasks.size() != 0){
                st = "rm " + NumberToString(tasks[selectTask]->getSerialNumber()) + "|ls";
                cl = parser->inputToCommandList(st);
                displayManager->setCommand(cl);
                if (list != originalList) list->removeTask(tasks[selectTask]->getSerialNumber());
            }
            break;
        case (int)'k':
            if (navigateRow > 0) navigateRow--;
            naiveDraw();
            break;
        case (int)'j':
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
                displayManager->setCommand(parser->inputToCommandList("edit "+NumberToString(tasks[selectTask]->getSerialNumber())+" -d \""+newDetail+"\""+" -g \""+newGrp+"\" -t " + newTime + " -p " + newPri+"|ls"));
            }
            break;
        case (int)'a':
            if (list!=originalList) break;
            newTaskSerial = originalList->getSerial()+1;
            tasks.push_back(new Task(currentTime(), 0, "New Task", 0, false,newTaskSerial, "default"));
            selectTask = tasks.size()-1;
            showDetail();
            naiveDraw();
            editDetail = editSelect();
            newGrp = editDetail[0];
            newTime = editDetail[1];
            newPri = editDetail[2];
            newDetail = editDetail[3];
            if (tasks[tasks.size()-1]) delete tasks[tasks.size()-1];
            displayManager->setCommand(parser->inputToCommandList("add -d \""+newDetail+"\""+" -g \""+newGrp+"\" -t " + newTime + " -p " + newPri +"|ls"));
            break;
        case (int)'s':
            search();
            break;
        case KEY_UP:
            if (selectTask > 0) selectTask--;
            if (selectTask >= 0 && selectTask < tasks.size() && taskStartAt[selectTask]<navigateRow) navigateRow = taskStartAt[selectTask];
            if (selectTask >= 0 && selectTask < tasks.size() && taskStartAt[selectTask+1]>navigateRow+mx-2) navigateRow = taskStartAt[selectTask+1]-mx+2;
            naiveDraw();
            break;
        case KEY_DOWN:
            if (selectTask+1 < tasks.size()) selectTask++;
            if (selectTask >= 0 && selectTask < tasks.size() && taskStartAt[selectTask]<navigateRow) navigateRow = taskStartAt[selectTask];
            if (selectTask >= 0 && selectTask < tasks.size() && taskStartAt[selectTask+1]>navigateRow+mx-2) navigateRow = taskStartAt[selectTask+1]-mx+2;
            naiveDraw();
            break;
        case (int)' ':
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
    list = result;
    originalList = result;
    draw();
}
void ListDisplayElement::selectUp(){
}
void ListDisplayElement::selectDown(){
}
void ListDisplayElement::navigateUp(){
}
void ListDisplayElement::navigateDown(){
}
void ListDisplayElement::reconstructLines(){
    int mx=0, my=0;
    getmaxyx(stdscr, mx, my);
   
    lines.clear();
    taskStartAt.clear(); 
    for (int i=0; i<tasks.size(); i++){
        taskStartAt.push_back(lines.size());
        if (! detailList[tasks[i] -> getSerialNumber()] ){
            lines.push_back("   ");
            string temps;
            temps = NumberToString(tasks[i]->getSerialNumber());
            lines[lines.size() - 1].append(temps);
            while (lines[lines.size() - 1].size() < 8) lines[lines.size() - 1].push_back(' ');
            if (tasks[i]->getIsFinished()) lines[lines.size() - 1].append("f ");
            else lines[lines.size() - 1].append("  ");         
            temps = tasks[i]->getDescription();
            int mlength = my - 5 - 10;
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
            while (temps != ""){
                lines.push_back("               "+temps.substr(0,lengthLimit));
                if (lengthLimit >= temps.size()) temps = "";
                else temps = temps.substr(lengthLimit,temps.size());
            }
            lines.push_back("        "+string(my-16,'-'));
        }
    }
    taskStartAt.push_back(lines.size());
}

void ListDisplayElement::refreshEditArea(WINDOW* win, int row0, int row1, int col0, int col1, string newStr, int startPos,int* cR, int* cC){
    int tmp = startPos;
    int curRow = row0,curCol = col0;
    for (int i=row0;i<=row1;i++)
        for (int j=col0;j<=col1;j++){
            if (tmp == newStr.size()) {curRow = i; curCol = j;tmp++;}
            move(i,j);
            addch(tmp<newStr.size()?newStr[tmp++]:' ');
        }
    move(curRow,curCol);
    *cR = curRow;
    *cC = curCol;
}
string ListDisplayElement::editArea(WINDOW* win,int row0,int row1,int col0,int col1,string st0){
    attron(A_REVERSE);
    row0+=win->_begy+1;
    row1+=win->_begy+1;
    col0+=win->_begx+1;
    col1+=win->_begx+1;
    curs_set(1);
    string newStr = st0;
    int startPos = 0;
    int msize = (row1 - row0 + 1) * (col1 - col0 + 1);
//    if (newStr.size()>=msize) startPos = newStr.size() - msize + 1;
    int curPos = newStr.size();
    int curRow,curCol;
    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&curRow,&curCol);
    bool flag = false;
    int tmp;
    while (!flag){
        int ch = getch();
        switch (ch){
            case 10:
            case 13:
                flag= true;
                break;
            case KEY_LEFT:
                if (curPos!=0 && !(curRow == row0 && curCol == col0)){
                    if (curCol == col0){ curCol = col1; curRow--;}
                    else curCol--;
                    curPos--;
                    move(curRow,curCol);
                }else if (curRow == row0 && curCol == col0 && !startPos ==0){
                    startPos-=col1-col0+1;
                    curPos--;
                    curCol = col1;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp);
                    move(curRow,curCol);
                }
                break;
            case KEY_RIGHT:
                if (curPos!=newStr.size() && !(curRow == row1 && curCol == col1)){
                    if (curCol == col1){ curCol = col0; curRow++;}
                    else curCol++;
                    curPos++;
                    move(curRow,curCol);
                }else if (curRow == row1 && curCol == col1 && curPos<newStr.size()){
                    startPos+=col1-col0+1;
                    curPos++;
                    curCol = col0;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp);
                    move(curRow,curCol);
                }
                break;
            case KEY_UP:
                if (curPos - (col1-col0+1) >=0 && curRow!=row0){
                    curRow--;
                    curPos-=col1-col0+1;
                    move(curRow,curCol);
                }else if( curRow == row0 && startPos>0){
                    tmp = curPos - startPos;
                    startPos = startPos - (col1-col0+1) >0? startPos - (col1-col0+1) : 0;
                    curPos = startPos+tmp;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp);
                    move(curRow,curCol);
                }
                break;
            case KEY_DOWN:
                if (curPos + col1-col0+1 <= newStr.size() && curRow!=row1){
                    curRow++;
                    curPos+=col1-col0+1;
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
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp);
                    move(curRow,curCol);
                }
                break;
            case KEY_BACKSPACE:
            case 8:
            case 127:
                if (!(curCol == col0 && curRow == row0) && curPos != 0){
                    newStr.erase(curPos - 1,1);
                    if (curCol == col0){ curCol = col1; curRow--;}
                    else curCol--;
                    curPos--;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp);
                    move(curRow,curCol);
                }else if (curPos !=0){
                    startPos -= col1-col0+1;
                    newStr.erase(curPos - 1,1);
//                    startPos--;
                    curPos--;
                    curCol = col1;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp);
                    move(curRow,curCol);
                }
                break;
            case KEY_ESC:
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
            default:
                if (curCol < col1){//curPos - startPos + 1<msize){
                    newStr.insert(curPos,(char*)&ch,1);
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp);
                    curPos++;
                    curCol++;
                    move(curRow,curCol);
                }else{
                    newStr.insert(curPos,(char*)&ch,1);
                    startPos+=col1-col0+1;
                    curPos++;
                    curCol = col0;
                    refreshEditArea(win,row0,row1,col0,col1,newStr,startPos,&tmp,&tmp);
                }
                break;
        }
    }
    curs_set(0);
    attroff(A_REVERSE);
    curRow = row0, curCol = col0;
    tmp = 0;
    for (int i=row0;i<=row1;i++)
        for (int j=col0;j<=col1;j++){
            if (tmp == newStr.size()) {curRow = i; curCol = j;}
             move(i,j);
             addch(tmp<newStr.size()?newStr[tmp++]:' ');
        }
    move(row0,col0);
    return newStr;
}
vector<string> ListDisplayElement::editSelect(){
    //detailList[selectTask] = true;
    //naiveDraw();
    showDetail();
    int mx=0, my=0;
    getmaxyx(listWindow, mx, my);
    string newGrp = editArea(listWindow,taskStartAt[selectTask] - navigateRow,taskStartAt[selectTask] - navigateRow,13,max(23,13+(tasks[selectTask]->getGroup()).size()),tasks[selectTask]->getGroup());
    int theRow = taskStartAt[selectTask]- navigateRow + listWindow->_begy;
    if (theRow + 12 >= mx+listWindow->_begy) theRow= mx+listWindow->_begy-13;
    int newTime = datePicker(tasks[selectTask]->getDeadline(),theRow,45);//editArea(listWindow,taskStartAt[selectTask]+1- navigateRow,taskStartAt[selectTask]+1- navigateRow,47,71,formatTime(tasks[selectTask]->getDeadline()).substr(0,24));
    naiveDraw();
    move(taskStartAt[selectTask]+1- navigateRow + listWindow->_begy+1,48);
    printw(((formatTime(newTime)).substr(0,24)).c_str());
    move(taskStartAt[selectTask] - navigateRow +listWindow->_begy+1,14);
    attron(A_BOLD);
    printw("%s----",newGrp.c_str());
    attroff(A_BOLD);
    string newPri = editArea(listWindow,taskStartAt[selectTask]+2- navigateRow,taskStartAt[selectTask]+2- navigateRow,25,27,NumberToString(tasks[selectTask]->getPriority()));
    string newDetail = editArea(listWindow,taskStartAt[selectTask]+4- navigateRow,taskStartAt[selectTask+1] -2- navigateRow,15,my-13,tasks[selectTask]->getDescription());
    //displayManager->setCommand(parser->inputToCommandList("edit "+NumberToString(tasks[selectTask]->getSerialNumber())+" -d \""+newDetail+"\""+" -g \""+newGrp+"\" -t " + newTime + " -p " + newPri));
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
            if (selectTask >= 0 && selectTask < tasks.size() && taskStartAt[selectTask+1]>navigateRow+mx-2) navigateRow = taskStartAt[selectTask+1]-mx+2;
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
    list = originalList;
}

void ListDisplayElement::search(){
    bool flag = false;
    searchKeyword = "";
    displayManager->echo("Search: "+searchKeyword);
    while (!flag){
        selectTask = 0;
        int ch = getch();
        switch (ch){
            case KEY_ESC:
                reset();
                draw();
                flag =true;
                break;
            case 10:
            case 13:
                flag = true;
                break;
            case KEY_BACKSPACE:
            case 8:
            case 127:
                if (searchKeyword.size()!=0) searchKeyword = searchKeyword.substr(0,searchKeyword.size() - 1);
                reset();
                displayManager->echo("Search: "+searchKeyword);
                list = list -> getTasks(new KFilter("*"+searchKeyword+"*"));
                draw(); 
                break;
            default:
                searchKeyword.push_back((char)ch);
                displayManager->echo("Search: "+searchKeyword);
                list = list -> getTasks(new KFilter("*"+searchKeyword+"*"));
                draw(); 
                break;
        }
    }
    displayManager->echo("Search finish");
}
void ListDisplayElement::restoreLastView(){
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
    printw("%34s"," ");
    curRow++;
    move(curRow,startCol);
    attron(A_REVERSE);
    printw("%15s %4d                ",months[curMon].c_str(),curYear);
    attroff(A_REVERSE);
    curRow++;
    move(curRow,startCol);
    attron(A_UNDERLINE); 
    printw("  Week  | Su Mo Tu We Th Fr Sa    ");
    attroff(A_UNDERLINE);
    curRow++;
    for (int i=0;i<6;i++){
        datetime = localtime(&startTime);
        int numOfWeek = (datetime->tm_yday)/7 + 1;
        move(curRow,startCol);
        printw("  %4d  |",numOfWeek);
        curCol += 9;
        for (int j=0;j<7;j++){
            move(curRow,curCol);
            datetime = localtime(&startTime);
            if (datetime->tm_mon == curMon) attron(A_BOLD);
            if (datetime->tm_mday == curDay && datetime->tm_mon == curMon) attron(A_REVERSE);
            printw("%3d",datetime->tm_mday);
            if (datetime->tm_mday == curDay && datetime->tm_mon == curMon) attroff(A_REVERSE);
            if (datetime->tm_mon == curMon) attroff(A_BOLD);
            startTime += 24*60*60;
            curCol+=3;
        }
        move(curRow,curCol);
        printw("    ");
        curRow+=1;
        curCol=startCol;
    }
    move(curRow,startCol);
    printw("%34s"," ");
    curRow++;
    refresh();
}

time_t ListDisplayElement::datePicker(time_t curTime,int startRow, int startCol){

//    time_t curTime = currentTime();
    drawCalendar(curTime,startRow,startCol);
    bool flag = false;

    while (!flag){
        int ch = getch();
        switch (ch){
            case 10:
            case 13:
                flag = true;
                break;
            case KEY_LEFT:
                curTime -= 24*60*60;
                break;
            case KEY_RIGHT:
                curTime += 24*60*60;
                break;
            case KEY_UP:
                curTime -= 7 * 24*60*60;
                break;
            case KEY_DOWN:
                curTime += 7 * 24*60*60;
                break;
            default:
                break;
        }
        drawCalendar(curTime,startRow,startCol);
    }
    return curTime;    
}
