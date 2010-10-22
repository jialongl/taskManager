/* Author: He Haocong */

KFilter::KFilter(string k){
  kString = k;
}
bool KFilter::filter(Task* task){
  return (task->matchKeyword(kString));
}
