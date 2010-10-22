/* Author: He Haocong */
#include "OFilter.h"
bool OFilter::filter(Task* task){
  return (task->getDeadline() < currentTime() && task->getIsFinished() == false);
}
