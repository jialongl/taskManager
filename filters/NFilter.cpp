/* Author: He Haocong */
#include "NFilter.h"
NFilter::NFilter(int num){
  n = num;
}

bool NFilter::filter(Task* task){
  return (task->getSerialNumber() == n);
}
