/* Author: He Haocong */

FFilter::FFilter(bool finish){
  finished = finish;
}

bool FFilter::filter(Task* task){
  return (task->getIsFinished() == finished);
}
