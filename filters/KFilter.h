/* Author: Liu Jialong */

#ifndef KFilterH
#define KFilterH

#include "Filter.h"

class KFilter: public Filter{
 private:
  string kString;

 public:
  KFilter(string k);
  bool filter(Task* task);
};

#endif
