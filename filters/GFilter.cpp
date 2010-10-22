/* Author: He Haocong */

GFilter::GFilter(string s){
  groups = s;
}

bool GFilter::filter(Task* task){
  return (task->getGroup() == groups);
}
