class Command{
public:
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
