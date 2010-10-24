/* Author: Liu Jialong */
/* Author: He Haocong */

#ifndef utilH
#define utilH

static string getRecordDirectory(){
  passwd *pwd = getpwuid( getuid() );
  return string(pwd->pw_dir) + "/record.xml";
}

static time_t currentTime(){
        time_t curTime;
        time(&curTime);
        return curTime; // + TIMEZONE * 3600;
}

static int min(int x,int y){ return x<y?x:y;}
static int max(int x,int y){ return x>y?x:y;}

static string formatTime(int x){
	time_t  t = x;
	return (string)ctime(&t);	
}

static int StringToNum(string s){
  if (s[0] == '-')
    return -StringToNum(s.substr(1, s.length()));

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

static string NumberToString(int x){
    stringstream ss("");
    ss<<x;
    return ss.str();
}

static bool tryMatch(string st1, string st2){
    st1 = '!' + st1;
    st2 = '!' + st2;
	vector< vector<bool> > match(st1.length()+1, vector<bool> (st2.length()+1));
	for (int i = 0; i<st1.length()+1; i++){
	    for (int j = 0; j<st2.length()+1; j++){
			if (i<=0&&j<=0) match[i][j] = true; else
			if (i<=0||j<=0) match[i][j] = false; else
			if (st2[j-1] == '*') match[i][j] = match[i][j - 1] || match[i - 1][j]; else
			if (st2[j-1] == '?') match[i][j] =  match[i - 1][j - 1]; else
			if (st2[j-1] == st1[i-1]) match[i][j] =  match[i - 1][j - 1]; else
				match[i][j]=false;
		}
	}
	return match[st1.length()][st2.length()];
}

static void displayHelp(){
	ifstream inf("man");
	//FILE* inf = fopen("man","r");
	char ch;
	//while (fscanf(inf,"%c",&ch) == 1){
	while (inf.get(ch))
	{
		cout<<ch;
	}
}

static WINDOW *create_newwin(int height, int width, int starty, int startx)
{   WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
//    wborder(local_win, '|', '|', '-','-','+','+','+','+');
    box(local_win, '|' , '-');      /* 0, 0 gives default characters 
				     * for the vertical and horizontal
				     * lines */
    wrefresh(local_win);            /* Show that box */

    return local_win;
}

static void destroy_win(WINDOW *local_win)
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

#endif
