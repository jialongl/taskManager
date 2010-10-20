#ifndef ListDisplayElementH
#define ListDisplayElementH
class ListDisplayElement:public DisplayElement{
private: 
    TaskList* list;
    WINDOW* listWindow;
    int navigateRow,selectTask;
    vector<bool> detailList;
    vector<string> lines;
    vector<Task*> tasks;
    vector<int> taskStartAt;
public:
    ListDisplayElement(TaskList* taskList);
    ~ListDisplayElement();
    void draw();
    void handleKey(int ch);
    void handleConfirm(bool flag);
    void handleResult(Result* result);
    void navigateDown();
    void navigateUp();
    void selectUp();
    void selectDown();
    void reconstructLines();
};
#endif
