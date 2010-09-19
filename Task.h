class Task{
private:
	time_t deadline;
	int priority;
	string description;
	int cronFreq;
	bool isFinished;
	int serialNumber;
	string group;

	bool vv(int i, int j){
		return (i<0 || j<0);
	}
	
	bool tryMatch(string st1, string st2){
		vector< vector<bool> > match;
		for (int i=0;i<st1.length();i++){
			for (int j=0;j<st2.length();j++){
				if (st2[j] == '*') match[i][j] = vv(i-1,j) || match[i - 1][j]; else
				if (st2[j] == '?') match[i][j] = vv(i-1,j-1) || match[i - 1][j - 1]; else
				if (st2[j] == st1[i]) match[i][j] = vv(i-1,j-1) ||  match[i - 1][j - 1]; else
					match[i][j] = false;
			}
		}
		return match[st1.length()-1][st2.length()-1];
	}
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
