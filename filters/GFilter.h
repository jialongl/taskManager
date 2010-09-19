class GFilter: public Filter{
private:
	string groups;
public:
	GFilter(string s){
		groups = s;
	}
	bool filter(Task* task){
		return (task->getGroup() == groups);
	}
};
