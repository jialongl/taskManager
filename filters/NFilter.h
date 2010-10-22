/* Author: Liu Jialong */

#ifndef NFilterH
#define NFilterH

#include "Filter.h"

class NFilter: public Filter{
 private:
  int n;

 public:
  NFilter(int num);
  bool filter(Task* task);
};

#endif
