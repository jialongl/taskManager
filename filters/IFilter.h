#ifndef IFilterH
#define IFilterH

#include "Filter.h"

class IFilter:public Filter{
private:
    time_t t1,t2;

public:
    IFilter(time_t tFrom, time_t tTo);
    bool filter(Task* task);
};

#endif
