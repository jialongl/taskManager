/* Author: He Haocong */

#ifndef FilterH
#define FilterH

#include "../includes.h"
#include "../Task.h"

class Filter{
 public:
  virtual bool filter(Task* task) = 0;
  virtual ~Filter(){};
};

#endif
