/* Author: Liu Jialong */

#ifndef GFilterH
#define GFilterH

class GFilter: public Filter{
 private:
  string groups;

 public:
  GFilter(string s);
  bool filter(Task* task);
};

#endif
