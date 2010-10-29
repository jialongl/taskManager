/* Author: Liu Jialong */
/* Author: He Haocong */

#ifndef utilH
#define utilH
#include "includes.h"

time_t currentTime();

bool isNumber(string s);

int min(int x,int y);
int max(int x,int y);

string formatTime(int x);

int StringToNum(string s);

string NumberToString(int x);

bool tryMatch(string st1, string st2);

void displayHelp();

WINDOW *create_newwin(int height, int width, int starty, int startx);

void destroy_win(WINDOW *local_win);

int lcs(string st1, string st2);

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
