/* Author: He Haocong */
class KFilter: public Filter{
private:
	string kString;
public:
	KFilter(string k){
		kString = k;
	}
	bool filter(Task* task){
		return (task->matchKeyword(kString));
	}
};
