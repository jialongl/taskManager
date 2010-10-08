/* Author: He Haocong */
class OFilter: public Filter{
public:
	bool filter(Task* task){
		return (task->getDeadline() < currentTime() && task->getIsFinished() == false);
	}
};
