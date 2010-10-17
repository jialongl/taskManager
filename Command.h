/* Author: He Haocong */
class Command{
public:
	/*Command(commandMethod mtd, string tskD, time_t dl,int pri, string grp, int cF, vector<sortKeyword_e> sK, vector<int> sNL, bool f, string fn, bool h){
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
	}*/

	Command(){
	  deadline = 0;
	  priority = 0;
	  group = "";
	  cronFreq = 0;
	  finished = false;
	  html = false;
	  keyword = "";
	  finishFlag = ALL;
	  overdue = false;
	  serialNumberList.clear();
	  sortKeyword.clear();
	  taskDescription = "";
	  filename = "record.xml";
	  deadline = currentTime();
	  method = NULLCOMMAND;
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
	string keyword;
	finishFlag_e finishFlag;
	bool overdue;
};

typedef vector<Command*> CommandList ;

