ListDisplayElement::ListDisplayElement(TaskList* taskList){
    originalList = taskList;
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
    if (detailList.size() == 0)
        for (int i=0; i<tasks.size(); i++) detailList.push_back(false); 
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
                st = "rm " + NumberToString(tasks[selectTask]->getSerialNumber());
                cl = parser->inputToCommandList(st);
                displayManager->setCommand(cl);
                if (list != originalList) list->removeTask(tasks[selectTask]->getSerialNumber());
            }
            break;
        case (int)'j':
            if (navigateRow > 0) navigateRow--;
            naiveDraw();
            break;
        case (int)'k':
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
            displayManager->setCommand(parser->inputToCommandList("add -d \""+newDetail+"\""+" -g \""+newGrp+"\" -t " + newTime + " -p " + newPri));
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
                if (detailList[selectTask]) hideDetail();
                else showDetail();
            }
            break;
        default:
            break;
    }
}
void ListDisplayElement::handleConfirm(bool flag){
}
void ListDisplayElement::handleResult(Result* result){
    list = result;
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
        if (! detailList[i] ){
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

string ListDisplayElement::editArea(WINDOW* win,int row0,int row1,int col0,int col1,string st0){
    row0+=win->_begy+1;
    row1+=win->_begy+1;
    col0+=win->_begx+1;
    col1+=win->_begx+1;
    attron(A_REVERSE);
    int msize = (row1-row0+1)*(col1-col0+1);
    curs_set(1);
    int curRow = row0, curCol = col0;
    string newStr = st0;
    int curPos = st0.size();
    int tmp = 0;
    for (int i=row0;i<=row1;i++)
        for (int j=col0;j<=col1;j++){
            if (tmp == newStr.size()) {curRow = i; curCol = j;tmp++;}
            move(i,j);
            addch(tmp<newStr.size()?newStr[tmp++]:' ');
        }
    move(curRow,curCol);
    bool flag = false;
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
                }
                break;
            case KEY_RIGHT:
                if (curPos!=newStr.size() && !(curRow == row1 && curCol == col1)){
                    if (curCol == col1){ curCol = col0; curRow++;}
                    else curCol++;
                    curPos++;
                    move(curRow,curCol);
                }
                break;
            case KEY_UP:
                if (curPos - (col1-col0+1) >=0 && curRow!=row0){
                    curRow--;
                    curPos-=col1-col0+1;
                    move(curRow,curCol);
                }
                break;
            case KEY_DOWN:
                if (curPos + col1-col0+1 < newStr.size() && curRow!=row1){
                    curRow++;
                    curPos+=col1-col0+1;
                    move(curRow,curCol);
                }
                break;
            case KEY_BACKSPACE:
            case 8:
            case 127:
                if (curPos!=0){
                    newStr.erase(curPos - 1,1);
                    if (curCol == col0){ curCol = col1; curRow--;}
                    else curCol--;
                    curPos--;
                    int tmpRow = curRow, tmpCol = curCol;
                    for (int i=curPos;i<newStr.size();i++){
                        move(tmpRow,tmpCol);
                        addch(newStr[i]);
                        if (tmpCol == col1){ tmpCol = col0; tmpRow++;}
                        else tmpCol++;
                    }
                    move(tmpRow,tmpCol);
                    addch(' ');
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
                if (newStr.size()+1<msize){
                    newStr.insert(curPos,(char*)&ch,1);
                    int tmpRow = curRow, tmpCol = curCol;
                    for (int i=curPos;i<newStr.size();i++){
                        move(tmpRow,tmpCol);
                        addch(newStr[i]);
                        if (tmpCol == col1) { tmpCol = col0; tmpRow++;}
                        else tmpCol++;
                    }
                    move(tmpRow,tmpCol);
                    addch(' ');
                    if (curCol == col1){ curCol = col0; curRow++;}
                    else curCol++;
                    curPos++;
                    move(curRow,curCol);
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
    string newGrp = editArea(listWindow,taskStartAt[selectTask] - navigateRow,taskStartAt[selectTask] - navigateRow,13,23,tasks[selectTask]->getGroup());
    string newTime = editArea(listWindow,taskStartAt[selectTask]+1- navigateRow,taskStartAt[selectTask]+1- navigateRow,47,71,formatTime(tasks[selectTask]->getDeadline()).substr(0,24));
    string newPri = editArea(listWindow,taskStartAt[selectTask]+2- navigateRow,taskStartAt[selectTask]+2- navigateRow,25,27,NumberToString(tasks[selectTask]->getPriority()));
    string newDetail = editArea(listWindow,taskStartAt[selectTask]+4- navigateRow,taskStartAt[selectTask+1] -2- navigateRow,15,my-13,tasks[selectTask]->getDescription());
    //displayManager->setCommand(parser->inputToCommandList("edit "+NumberToString(tasks[selectTask]->getSerialNumber())+" -d \""+newDetail+"\""+" -g \""+newGrp+"\" -t " + newTime + " -p " + newPri));
    vector<string> ans;
    ans.push_back(newGrp);
    ans.push_back(newTime);
    ans.push_back(newPri);
    ans.push_back(newDetail);
    return ans;
}
void ListDisplayElement::showDetail(){
    int mx,my;
    getmaxyx(listWindow,mx,my);
    if (tasks.size()!=0){
//        if (detailList[selectTask]) detailList[selectTask] = false;
        detailList[selectTask] = true;
        reconstructLines();
        if (detailList[selectTask]){
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
        detailList[selectTask] = false;
        naiveDraw();
    }
}

void ListDisplayElement::reset(){
    list = originalList;
}

void ListDisplayElement::search(){
    bool flag = false;
    searchKeyword = "";
    IOModule->echo("Search: "+searchKeyword);
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
                IOModule->echo("Search: "+searchKeyword);
                list = list -> getTasks(new KFilter("*"+searchKeyword+"*"));
                draw(); 
                break;
            default:
                searchKeyword.push_back((char)ch);
                IOModule->echo("Search: "+searchKeyword);
                list = list -> getTasks(new KFilter("*"+searchKeyword+"*"));
                draw(); 
                break;
        }
    }
    IOModule->echo("Search finish");
}
