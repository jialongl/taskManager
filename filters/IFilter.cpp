#include "IFilter.h"

IFilter::IFilter(time_t tFrom, time_t tTo){
    t1 = tFrom;
    t2 = tTo;
}

bool IFilter::filter(Task* task){
    return (task->getDeadline()>=t1 && task->getDeadline()<t2);
}
