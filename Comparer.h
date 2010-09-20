class Comparer{
private:
	vector<sortKeyword_e> *keywords;
public:
	Comparer(vector<sortKeyword_e> keys){
		keywords = &keys;
	}

	Comparer(){
		keywords = new vector<sortKeyword_e>;
		keywords->push_back(SERIAL_NUMBER);
	}

	int compareWithKeyword(Task* task1, Task* task2, sortKeyword_e sk){
		switch (sk){
			case DEADLINE:
				if (task1->getDeadline() < task2->getDeadline()) return -1;
				if (task1->getDeadline() == task2->getDeadline()) return 0;
				if (task1->getDeadline() > task2->getDeadline()) return 1;
				break;
			case PRIORITY:
				if (task1->getPriority() > task2->getPriority()) return -1;
				if (task1->getPriority() == task2->getPriority()) return 0;
				if (task1->getPriority() < task2->getPriority()) return 1;
				break;
			case SERIAL_NUMBER:	
				if (task1->getSerialNumber() < task2->getSerialNumber()) return -1;
				if (task1->getSerialNumber() == task2->getSerialNumber()) return 0;
				if (task1->getSerialNumber() > task2->getSerialNumber()) return 1;
				break;
		}
	}

	bool compare(Task* task1, Task* task2){
		for (vector<sortKeyword_e>::iterator it = keywords->begin(); it != keywords->end(); it++){
			int x = compareWithKeyword(task1, task2, *it);
			if (x<0) return true;
			if (x>0) return false;
		}		
		return true;
	}
};
