class Filter{
public:
	virtual bool filter(Task* task) =0;
	virtual ~Filter(){};
};
