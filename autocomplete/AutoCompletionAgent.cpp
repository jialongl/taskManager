#include "AutoCompletionAgent.h"

AutoCompletionAgent::AutoCompletionAgent(){
    enabled = true;
    tree = new DictTree();
}
AutoCompletionAgent::~AutoCompletionAgent(){
    delete tree;
}

void AutoCompletionAgent::disable(){
    enabled=false;
}
void AutoCompletionAgent::enable(){
    enabled=true;
}

void AutoCompletionAgent::tell(string st){
    for (int i=0;i<st.length();i++){
        st[i] = toLowerCase(st[i]);
        if (! isChar(st[i])) return;
    } 
    tree->tell(st);
}
string AutoCompletionAgent::ask(string st){
    if (enabled=false) return "";
    //misterious
    if (st.length()<2) return "";
    for (int i=0;i<st.length();i++){
        st[i] = toLowerCase(st[i]);
        if (! isChar(st[i])) return "";
    } 
    return tree->ask(st);
}

bool AutoCompletionAgent::isChar(char ch){
    return ((ch>=97 && ch<97+26) || (ch>=48 && ch<58)); 
}

char AutoCompletionAgent::toLowerCase(char ch){
    if (ch < 97 && ch>=65) ch += (97-65);
    return ch;
}

bool AutoCompletionAgent::isSeparator(char ch){
/*    if (ch == ' ') return ture;
    if (ch == ',') return ture;
    if (ch == '.') return ture;
    if (ch == '|') return ture;
    if (ch == '-') return ture;
    if (ch == '"') return ture;
    if (ch == '\'') return ture;
    if (ch == '?') return ture;
    if (ch == '!') return ture;
    if (ch == '@') return ture;
    if (ch == '#') return ture;
    if (ch == '<') return ture;
    if (ch == '>') return ture;
    if (ch == '&') return ture;
    if (ch == '(') return ture;
    if (ch == ')') return ture;
    if (ch == '=') return ture;
    if (ch == '/') return ture;
    if (ch == ':') return ture;
    if (ch == ';') return ture;
    */
    return !(isChar(toLowerCase(ch)));
}

vector<string> AutoCompletionAgent::tokenize(string s){
    vector<string> ans;
    ans.clear();
    int pos = 0;
    while (pos < s.length()){
        while (pos < s.length() && isSeparator(s[pos])) pos++;
        int pos0 = pos;
        int len = 0;
        while (pos < s.length() && !isSeparator(s[pos])){ pos++; len++; }
        if (len!=0) ans.push_back(s.substr(pos0,len));
    }
    return ans;
}

void AutoCompletionAgent::analysis(TaskList* list){
    Comparer* cmp = new Comparer();
    vector<Task*> tasks = list->sort(cmp);
    delete cmp;
    for (int i=0;i<tasks.size();i++){
        vector<string> tokens = tokenize(tasks[i]->getDescription());
        for (int j=0;j<tokens.size();j++)
            tell(tokens[j]);
        tokens = tokenize(tasks[i]->getGroup());
        for (int j=0;j<tokens.size();j++)
            tell(tokens[j]);
    }
}

void AutoCompletionAgent::analysis(string sentense){
    vector<string> tokens = tokenize(sentense);
    for (int j=0;j<tokens.size();j++)
        tell(tokens[j]);
}
