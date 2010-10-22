/* Author: He Haocong */
#include "GFilter.h"

GFilter::GFilter(string s){
  groups = s;
}

bool GFilter::filter(Task* task){
  return (task->getGroup() == groups);
}
