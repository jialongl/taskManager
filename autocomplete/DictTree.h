#ifndef DictTreeH
#define DictTreeH

#include "../includes.h"
class DictTree{
public:
    DictTree();
    ~DictTree();
    bool hasTerminal;
    int childrenCount;
    string ask(string st);
    void tell(string st);
private:
    DictTree* children[36];
    /* 0~25 = a~z, 26~35 = 0..9*/
};
#endif
