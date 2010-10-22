#ifndef DisplayElementH
#define DisplayElementH

#include "../../includes.h" 
#include "../../Result.h"

class DisplayElement{
protected:
    DisplayElement* parent;
public:
    displayElementType type;
    virtual ~DisplayElement(){};
    void setParent(DisplayElement* element);
    virtual void draw()=0;
    virtual void handleKey(int ch){};
    virtual void handleConfirm(bool flag){};
    virtual void handleResult(Result* result){};
    virtual void reset(){};
};
#endif
