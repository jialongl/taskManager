#include "DictTree.h"

DictTree::DictTree(){
    hasTerminal = false;
    childrenCount = 0;
    for (int i=0;i<26;i++)
        children[i] = NULL;
}

DictTree::~DictTree(){
    for (int i=0;i<26;i++)
        if (children[i] != NULL) delete children[i];
}

string DictTree::ask(string st){
//    cout<<"tree ask"+st<<endl;
    if (st == ""){
        if (hasTerminal || (childrenCount == 0)) return "";
        else{
            for (int i=0;i<26;i++)
                if (children[i] != NULL){
                    string ans = children[i]->ask(st);
                    return ans.insert(0,1,i+97);
                    break;
                }
            return "";
        }
    }else{
        int ch = st[0] - 97;
        if (children[ch] == NULL) return "";
        return children[ch] -> ask(st.substr(1,st.length() - 1));
    }
}

void DictTree::tell(string st){
    if (st == "") {
        hasTerminal = true;
        return;
    }
    int ch = st[0] - 97;
    if (children[ch] == NULL){
        children[ch] = new DictTree();
        childrenCount++;
        children[ch] -> tell(st.substr(1,st.length()-1));
    }else{
        children[ch] -> tell(st.substr(1,st.length()-1));
    }
}
