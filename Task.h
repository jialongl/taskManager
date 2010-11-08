/* Author: Liu Jialong */

#ifndef TaskH
#define TaskH

#include "includes.h"
#include "util.h"

class Task{
 private:
  time_t deadline;
  time_t finishTime;
  int priority;
  string description;
  bool isFinished;
  int serialNumber;
  string group;

 public:
  Task(time_t deadline, int priority, string description, int cronFreq, bool isFinished, int serialNumber, string group, time_t ft);
  ~Task();
  void setPriority(int x);
  void setDeadline(time_t t);
  void setFinishTime(time_t t);
  void setDescription(string s);
  void setGroup(string s);
  void setSerialNumber(int x);
  void setIsFinished(bool f);
  time_t getDeadline();
  time_t getFinishTime();
  int getPriority();
  string getDescription();
  bool getIsFinished();
  int getSerialNumber();
  string getGroup();
  bool matchKeyword(string keyword);
  Task* clone();
};

#endif
