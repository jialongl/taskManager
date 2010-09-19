class Command{
public:
	Command(commandMethod mtd, string tskD, time_t dl,int pri, string grp, int cF, vector<sortKeyword_e> sK, vector<int> sNL, bool f, string fn, bool h){
		method = mtd;
		taskDescription = tskD;
		deadline = dl;
		priority = pri;
		group = grp;
		cronFreq = cF;
       		sortKeyword = sK;
	    	serialNumberList = sNL;		    
		finished = f;
		filename = fn;
		html = h;
	}

	Command(){
	  deadline = 0;
	  pri = 0;
	  group = NULL;
	  cronFreq = 0;
	  sortKeyword = new vector<sortKeyword_e>;
	  serialNumberList = new vector<int>;
	  finished = false;
	  html = false;
	}

	commandMethod method;
	string taskDescription;
	time_t deadline;
	int priority;
	string group;
	int cronFreq;
	vector<sortKeyword_e> sortKeyword;
	vector<int> serialNumberList;
	bool finished;
	string filename;
	bool html;
};
