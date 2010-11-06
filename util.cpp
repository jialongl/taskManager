/* Author: Liu Jialong */
/* Author: He Haocong */

#ifndef utilCPP
#define utilCPP

#include "util.h"

time_t currentTime(){
        time_t curTime;
        time(&curTime);
        return curTime; // + TIMEZONE * 3600;
}

bool isNumber(string s){
  if (s[0] == '-')
    return isNumber(s.substr(1, s.length()-1));

    for (int i=0;i<s.length();i++)
      if (!isDigit(s[i])) return false;
    return true;
}

bool isDigit(char ch){
    return (ch >= 48 && ch <= 57);
}

int min(int x,int y)
{ return x<y?x:y;}
int max(int x,int y)
{ return x>y?x:y;}

string formatTime(int x){
    if (x == NO_SPECIFIC_DEADLINE) return "Anytime";
	time_t  t = x;
	return ((string)ctime(&t)).substr(0,24);	
}

int StringToNum(string s){
  if (s[0] == '-')
    return -StringToNum(s.substr(1, s.length()-1));

  int ans = 0;
  for (unsigned i=0; i < s.size(); i++){
    if (s[i] == ' ') continue;
    if (s[i] >= 48 && s[i] <= 57)
      ans = ans*10 + ((int) s[i]) - 48;
    else
      throw EXCEPTION_NOT_A_NUMBER;
  }
  return ans;
}

string NumberToString(int x){
    stringstream ss("");
    ss<<x;
    return ss.str();
}

bool tryMatch(string st1, string st2){
    st1 = '!' + st1;
    st2 = '!' + st2;
	vector< vector<bool> > match(st1.length()+1, vector<bool> (st2.length()+1));
	for (int i = 0; i<st1.length()+1; i++){
	    for (int j = 0; j<st2.length()+1; j++){
			if (i<=0&&j<=0) match[i][j] = true; else
			if (i<=0||j<=0) match[i][j] = false; else
			if (st2[j-1] == '*') match[i][j] = match[i][j - 1] || match[i - 1][j]; else
			if (st2[j-1] == '?') match[i][j] =  match[i - 1][j - 1]; else
			if (st2[j-1] == st1[i-1] || abs(st2[j-1] - st1[i-1] == 32)) match[i][j] =  match[i - 1][j - 1]; else
				match[i][j]=false;
		}
	}
	return match[st1.length()][st2.length()];
}

void displayHelp(){
	ifstream inf("man");
	//FILE* inf = fopen("man","r");
	char ch;
	//while (fscanf(inf,"%c",&ch) == 1){
	while (inf.get(ch))
	{
		cout<<ch;
	}
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{   WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
//    wborder(local_win, '|', '|', '-','-','+','+','+','+');
    box(local_win, '|' , '-');      /* 0, 0 gives default characters 
				     * for the vertical and horizontal
				     * lines */
    wrefresh(local_win);            /* Show that box */

    return local_win;
}

void destroy_win(WINDOW *local_win)
{   
    /* box(local_win, ' ', ' '); : This won't produce the desired
     * result of erasing the window. It will leave it's four corners 
     * and so an ugly remnant of window. 
     */
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    /* The parameters taken are 
     * 1. win: the window on which to operate
     * 2. ls: character to be used for the left side of the window 
     * 3. rs: character to be used for the right side of the window 
     * 4. ts: character to be used for the top side of the window 
     * 5. bs: character to be used for the bottom side of the window 
     * 6. tl: character to be used for the top left corner of the window 
     * 7. tr: character to be used for the top right corner of the window 
     * 8. bl: character to be used for the bottom left corner of the window 
     * 9. br: character to be used for the bottom right corner of the window
     */
    wrefresh(local_win);
    delwin(local_win);
}

int lcs(string st1, string st2){
    if (st1 == "" || st2 == "") return 0;
//    cout<<"comparing with: "<<st1<<"!!!"<<st2<<endl;
    int f[2][MAX_LEN];
    for (int i=0;i<st1.size();i++)
        for (int j=0;j<st2.size();j++)
            if (st1[i] == st2[j]) 
                f[i%2][j] = (i-1<0||j-1<0)?1:f[(i+1)%2][j-1] + 1;
            else 
                f[i%2][j] = max( (i-1<0)?0:f[(i+1)%2][j] , (j-1<0)?0:f[i%2][j-1] );
//    cout<<f[(st1.size() -1)%2][st2.size()-1]*100/st2.size()<<"%"<<endl;
    return f[(st1.size() -1)%2][st2.size()-1]*100/max(st2.size(),st1.size());
}

string flaten(int argc, char* argv[]){
    string ans = "";
    for (int i=1;i<argc;i++){
        if (i!=1) ans.push_back(' ');
        ans = ans + string(argv[i]);
    }
    return ans;
}

#ifdef WIN32
#include <windows.h>
  //#define RCFILE "%USERPROFILE\\.tmrc"
string getRecordDirectory(){
	char profilepath[250];
	LPCSTR userprofile = "%userprofile%";
	ExpandEnvironmentStrings(userprofile,profilepath,250);
	string s = string(profilepath);
	//cvtLPW2stdstring(s,profilepath);
	//printf("%s",profilepath);
	return s+"\\record.xml";
}
string getRcDirectory(){
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
string getRecordDirectory(){
  passwd *pwd = getpwuid( getuid() );
  return string(pwd->pw_dir) + "/record.xml";
}
string getRcDirectory(){
  passwd *pwd = getpwuid( getuid() );
  return string(pwd->pw_dir) + "/.tmrc";
}
#endif

#endif
