/* Author: He Haocong */

bool OFilter::filter(Task* task){
  return (task->getDeadline() < currentTime() && task->getIsFinished() == false);
}
