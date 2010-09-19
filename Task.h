class Task{
private:
	time_t deadline;
	int priority;
	string description;
	int cronFreq;
	bool isFinished;
	int serialNumber;
	string group;

public:
	Task(time_t deadline, int priority, string description, int cronFreq, bool isFinished, int serialNumber, string group){
		setDeadline(deadline);
		setPriority(priority);
		setDescription(description);
		setCronFreq(cronFreq);
		setIsFinished(isFinished);
		setSerialNumber(serialNumber);
		setGroup(group);
	}

	void setPriority(int x){
		priority = x;
	}
	void setDescription(string s){
		description = s;
	}	
	void setDeadline(time_t t){
		deadline = t;
	}
	void setGroup(string s){
		group = s;
	}
	void setCronFreq(int x){
		cronFreq = x;
	}
	void setSerialNumber(int x){
		serialNumber = x;
	}
	void setIsFinished(bool f){
		isFinished = f;
	}
	
	time_t getDeadline(){
		return deadline;
	}
	int getPriority(){
		return priority;
	}
	string getDescription(){
		return string(description);
	}
	int getCronFreq(){
		return cronFreq;
	}
	bool getIsFinished(){
		return isFinished;
	}
	int getSerialNumber(){
		return serialNumber;
	}
	string getGroup(){
		return string(group);
	}

	bool matchKeyword(string keyword){
		return tryMatch(description, keyword);	
	}	
};
