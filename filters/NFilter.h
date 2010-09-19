class NFilter: public Filter{
private:
	int n;
public:
	NFilter(int num){
		n = num;
	}
	bool filter(Task* task){
		return (task->getSerialNumber() == n);
	}
};
