#ifndef ComparerH
#define ComparerH

#include "includes.h"
#includes "Task.h"

class Comparer{
 private:
  vector<sortKeyword_e> *keywords;

 public:
  Comparer();
  ~Comparer();
  int compareWithKeyword(Task* t1, Task* t2, sortKeyword_e sk);
  bool comparer(Task* t1, Task* t2);
}

#endif
