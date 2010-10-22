/* Author: Liu Jialong */

#ifndef CommandH
#define CommandH

#include "includes.h"

class Command{
 public:
  
  commandMethod method;
  string taskDescription;
  time_t deadline;
  int priority;
  string group;
  int cronFreq;
  vector<sortKeyword_e> sortKeyword;
  vector<int> serialNumberList;
  bool finished;
  string filename;
  bool html;
  string keyword;
  finishFlag_e finishFlag;
  bool overdue;

  Command();
};

typedef vector<Command*> CommandList;

#endif
