/* Author: Liu Jialong */
/* Author: He Haocong */

#ifndef utilH
#define utilH
#include "includes.h"

time_t currentTime();

bool isNumber(string s);
bool isDigit(char ch);

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

string flaten(int argc, char* argv[]);

string getRecordDirectory();
string getRcDirectory();

#define RECORDFILE getRecordDirectory()
#define RCFILE getRcDirectory()
#endif
