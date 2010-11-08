#ifndef AutoCompletionAgentH
#define AutoCompletionAgentH

#include "../includes.h"
#include "DictTree.h"
#include "../TaskList.h"

class AutoCompletionAgent{
public:
    string ask(string st);
    void tell(string st);
    AutoCompletionAgent();
    ~AutoCompletionAgent();
    void analysis(TaskList* list);
    void analysis(string sentense);
    bool isSeparator(char ch);
    void disable();
    void enable();
private:
    bool enabled;
    DictTree* tree;
    bool isChar(char ch);
    char toLowerCase(char ch);
    vector<string> tokenize(string s);
};

#endif

