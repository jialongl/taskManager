/* Author: Liu Jialong */
/* Author: He Haocong */
#ifndef utilH
#define utilH
time_t currentTime();
int min(int x,int y);
int max(int x,int y);
string formatTime(int x);
int StringToNum(string s);
string NumberToString(int x);
bool tryMatch(string st1, string st2);
void displayHelp();
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
#endif
