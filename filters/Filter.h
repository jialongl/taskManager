/* Author: He Haocong */

#ifndef FilterH
#define FilterH

class Filter{
 public:
  virtual bool filter(Task* task) = 0;
  virtual ~Filter(){};
};

#endif
