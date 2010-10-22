/* Author: Liu Jialong */

#ifndef NFilterH
#define NFilterH

class NFilter: public Filter{
 private:
  int n;

 public:
  NFilter(int num);
  bool filter(Task* task);
};

#endif
