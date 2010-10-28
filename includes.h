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
#include "util.h"

#ifdef WIN32
#include <windows.h>
  //#define RCFILE "%USERPROFILE\\.tmrc"
static string getRecordDirectory(){
	char profilepath[250];
	LPCSTR userprofile = "%userprofile%";
	ExpandEnvironmentStrings(userprofile,profilepath,250);
	string s = string(profilepath);
	//cvtLPW2stdstring(s,profilepath);
	//printf("%s",profilepath);
	return s+"\\record.xml";
}
static string getRcDirectory(){
	char profilepath[250];
	LPCSTR userprofile = "%userprofile%";
	ExpandEnvironmentStrings(userprofile,profilepath,250);
	string s = string(profilepath);
	//cvtLPW2stdstring(s,profilepath);
	//printf("%s",profilepath);
	return s+"\\tmrc.txt";
}
#else
  /* #define RECORDFILE "~/record.xml" */
  /* #define RCFILE     "~/.tmrc" */

  #include <cerrno>
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <pwd.h>
  #include <unistd.h>
static string getRecordDirectory(){
  passwd *pwd = getpwuid( getuid() );
  return string(pwd->pw_dir) + "/record.xml";
}
static string getRcDirectory(){
  passwd *pwd = getpwuid( getuid() );
  return string(pwd->pw_dir) + "/.tmrc";
}
#endif

#define RECORDFILE getRecordDirectory()
#define RCFILE getRcDirectory()

#endif

