/* Author: He Haocong */

#ifndef includesH
#define includesH


#define TIMEZONE 8
#define MAX_LEN 1024
#define MAX_UNDO 1000

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

#ifdef WIN32
#include "curses.h"
#else
#include <ncurses.h>
#endif


#include "enums.h"
//#include "util.h"

#define _NORMAL COLOR_PAIR(1)
#define _REVERSE A_REVERSE//COLOR_PAIR(2)
#define _BOLD COLOR_PAIR(3)
#define _UNDERLINE COLOR_PAIR(4)
#define _BLINK COLOR_PAIR(8)
#define _SELECT COLOR_PAIR(6)
#define _EDIT COLOR_PAIR(7)
#define _EDITTED COLOR_PAIR(8)//A_BOLD//COLOR_PAIR(8)
#define _TIMELINE COLOR_PAIR(9)
#define _TASKDAY COLOR_PAIR(10)


#endif

