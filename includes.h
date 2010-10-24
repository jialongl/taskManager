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

#include <cerrno>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>


#ifdef WIN32
  #include "curses.h"
  /* #define RECORDFILE "%USERPROFILE%\\record.xml" */
  /* #define RCFILE "%USERPROFILE\\.tmrc" */

#else
  #include <ncurses.h>
  /* #define RECORDFILE "~/record.xml" */
  /* #define RCFILE     "~/.tmrc" */

#endif

#define RECORDFILE getRecordDirectory()

#include "enums.h"
#include "util.h"

#endif

