#ifndef ListDisplayElementH
#define ListDisplayElementH

#include "../../includes.h"
#include "../../TaskList.h"
#ifdef WIN32
    #include "../../curses.h"
#else 
    #include <ncurses.h>
#endif
#include "../../Result.h"
#include "../../Parser.h"
#include "../../Command.h"
#include "../../Comparer.h"
#include "DisplayElement.h"
#include "DisplayManager.h"
#include "../../filters/IFilter.h"

class ListDisplayElement:public DisplayElement{
private: 
    TaskList *list,*originalList;
    string searchKeyword;
    WINDOW* listWindow;
    int navigateRow,selectTask;
    map<int,bool> detailList;
    vector<string> lines;
    vector<Task*> tasks;
    vector<int> taskStartAt;
    vector<int> taskFinishAt;
    int lastSelectedSn;
    int lastNavigateToSelect;
    Parser* parser;
    DisplayManager* displayManager;
public:
    ListDisplayElement(TaskList* taskList,Parser* parser,DisplayManager* dm);
    ~ListDisplayElement();
    void draw();
    void naiveDraw();
    void handleKey(int ch);
    void handleConfirm(bool flag);
    void handleResult(Result* result);
    void reconstructLines();
    string editArea(WINDOW* win,int row0,int row1,int col0,int col1,string st0);
    void refreshEditArea(WINDOW* win, int row0, int row1, int col0, int col1, string newStr, int startPos, int* cR,int* cC);
    vector<string> editSelect();
    void showDetail();
    void hideDetail();
    void reset();
    void search();
    void restoreLastView();
    void resize(int row0);
    time_t datePicker(time_t curTime, int startRow, int startCol);
    void drawCalendar(time_t theTime, int startRow, int startCol);
    void drawTime(int year,int mon,int day,int hourMinSec[],int curFoc,int startRow,int startCol);
    void drawSelectNumber();
    string formatDate(time_t t);
    string lineWithNewGroup(int i,string group);
    bool ListDisplayElement::is_time(string st);
    void ListDisplayElement::selectByCalendar();
};

#endif
