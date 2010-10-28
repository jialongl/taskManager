/* Author: Liu Jialong */

#ifndef TaskH
#define TaskH

#include "includes.h"

class Task{
 private:
  time_t deadline;
  int priority;
  string description;
  bool isFinished;
  int serialNumber;
  string group;

 public:
  Task(time_t deadline, int priority, string description, int cronFreq, bool isFinished, int serialNumber, string group);
  void setPriority(int x);
  void setDeadline(time_t t);
  void setDescription(string s);
  void setGroup(string s);
  void setSerialNumber(int x);
  void setIsFinished(bool f);
  time_t getDeadline();
  int getPriority();
  string getDescription();
  bool getIsFinished();
  int getSerialNumber();
  string getGroup();
  bool matchKeyword(string keyword);
  Task* clone();
};

#endif
