/* Author: Liu Jialong */

#ifndef ComparerH
#define ComparerH

#include "includes.h"
#include "Task.h"

class Comparer{
 private:

 public:
  vector<sortKeyword_e> *keywords;
  Comparer(vector<sortKeyword_e> keys);
  Comparer();
  ~Comparer();
  int compareWithKeyword(Task* t1, Task* t2, sortKeyword_e sk);
  bool compare(Task* t1, Task* t2);
};

#endif
