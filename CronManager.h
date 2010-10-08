/* Author: He Haocong */
class CronManager{
public:
	CronManager(){
	}

	time_t lastTime;

	void newTasks(time_t lastT, time_t nowT){
		//abc
		lastTime = nowT;
	}

};

CronManager *cronManager;
