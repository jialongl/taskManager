/* Author: Liu Jialong */

#ifndef GFilterH
#define GFilterH

#include "Filter.h"

class GFilter: public Filter{
 private:
  string groups;

 public:
  GFilter(string s);
  bool filter(Task* task);
};

#endif
