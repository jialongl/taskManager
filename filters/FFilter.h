/* Author: He Haocong */
class FFilter: public Filter{
private:
	bool finished;
public:
	FFilter(bool finish){
		finished = finish;
	}
	bool filter(Task* task){
		return (task->getIsFinished() == finished);
	}
};
