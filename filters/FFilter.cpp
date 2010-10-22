/* Author: He Haocong */
#include "FFilter.h"
FFilter::FFilter(bool finish){
  finished = finish;
}

bool FFilter::filter(Task* task){
  return (task->getIsFinished() == finished);
}
