/* Author: Liu Jialong */

#ifndef OFilterH
#define OFilterH

#include "Filter.h"

class OFilter: public Filter{
 public:
  bool filter(Task* task);
};

#endif
