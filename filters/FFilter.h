/* Author: Liu Jialong */

#ifndef FFilterH
#define FFilterH

#include "Filter.h"

class FFilter:public Filter{
 private:
  bool finished;

 public:
  FFilter(bool finish);
  bool filter(Task* task);
};

#endif
