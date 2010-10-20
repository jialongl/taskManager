ListDisplayElement::ListDisplayElement(TaskList* taskList){
    list = taskList;
    navigateRow = 0;
    selectTask = 0;
    int mx=0, my=0;
    getmaxyx(stdscr, mx, my);
    int height = mx - 5;
    int width = my;
    int startx = 4;
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
}
void ListDisplayElement::handleKey(int ch){
    int mx,my;
    getmaxyx(listWindow,mx,my);
    string st;
    CommandList cl;
    switch (ch){
        case (int)'f':
            st = "finish " + NumberToString(tasks[selectTask]->getSerialNumber());
            cl = parser->inputToCommandList(st);
            displayManager->setCommand(cl);
            break;
        case (int)'d':
            st = "rm " + NumberToString(tasks[selectTask]->getSerialNumber());
            cl = parser->inputToCommandList(st);
            displayManager->setCommand(cl);
            break;
        case (int)'k':
            if (navigateRow != 0) navigateRow--;
            draw();
            break;
        case (int)'j':
            if (navigateRow+1 < lines.size()) navigateRow++;
            draw();
            break;
        case KEY_UP:
            if (selectTask != 0) selectTask--;
            if (selectTask < tasks.size() && taskStartAt[selectTask]<navigateRow) navigateRow = taskStartAt[selectTask];
            draw();
            break;
        case KEY_DOWN:
            if (selectTask+1 < tasks.size()) selectTask++;
            if (selectTask < tasks.size() && taskStartAt[selectTask+1]>navigateRow+mx-2) navigateRow = taskStartAt[selectTask+1]-mx+2;
            draw();
            break;
        case (int)' ':
            if (detailList[selectTask]) detailList[selectTask] = false;
            else detailList[selectTask] = true;
            reconstructLines();
            draw();
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
}
