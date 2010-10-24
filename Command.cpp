/* Author: He Haocong */

/*Command(commandMethod mtd, string tskD, time_t dl,int pri, string grp, int cF, vector<sortKeyword_e> sK, vector<int> sNL, bool f, string fn, bool h){
  method = mtd;
  taskDescription = tskD;
  deadline = dl;
  priority = pri;
  group = grp;
  cronFreq = cF;
  sortKeyword = sK;
  serialNumberList = sNL;		    
  finished = f;
  filename = fn;
  html = h;
  }*/

#include "Command.h"

Command::Command(){
  deadline = 0;
  priority = 0;
  group = "";
  cronFreq = 0;
  finished = false;
  html = false;
  keyword = "";
  finishFlag = ALL;
  overdue = false;
  serialNumberList.clear();
  sortKeyword.clear();
  taskDescription = "";
  filename = "";
  deadline = currentTime();
  method = NULLCOMMAND;
}
