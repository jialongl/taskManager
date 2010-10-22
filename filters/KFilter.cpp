/* Author: He Haocong */
#include "KFilter.h"

KFilter::KFilter(string k){
  kString = k;
}
bool KFilter::filter(Task* task){
  return (task->matchKeyword(kString));
}
