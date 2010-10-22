#ifndef ListDisplayElementH
#define ListDisplayElementH
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
    int lastSelectedSn;
    int lastNavigateToSelect;
public:
    ListDisplayElement(TaskList* taskList);
    ~ListDisplayElement();
    void draw();
    void naiveDraw();
    void handleKey(int ch);
    void handleConfirm(bool flag);
    void handleResult(Result* result);
    void navigateDown();
    void navigateUp();
    void selectUp();
    void selectDown();
    void reconstructLines();
    string editArea(WINDOW* win,int row0,int row1,int col0,int col1,string st0);
    void refreshEditArea(WINDOW* win, int row0, int row1, int col0, int col1, string newStr, int startPos, int* cR,int* cC);
    vector<string> editSelect();
    void showDetail();
    void hideDetail();
    void reset();
    void search();
    void restoreLastView();
};
#endif
