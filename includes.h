/* Author: He Haocong */

#ifndef includesH
#define includesH


#define TIMEZONE 8
#define MAX_LEN 1024

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

#ifndef WIN32
  #include <ncurses.h>
  #define HOME "%USERPROFILE%"

#else
  #include "curses.h"
  #define HOME "~"

#endif

#include "enums.h"
#include "util.h"

#endif

