time_t currentTime(){
        time_t curTime;
        time(&curTime);
        return curTime + TIMEZONE * 60 * 60;
}

int StringToNum(string s){
  if (s[0] == '-')
    return -StringToNum(s.substr(1, s.length()));

  int ans = 0;
  for (unsigned i=0; i < s.size(); i++){
    if (s[i] >= 48 && s[i] <= 57)
      ans = ans*10 + ((int) s[i]) - 48;
    else
      throw EXCEPTION_NOT_A_NUMBER;
  }
  return ans;
}

	
	bool tryMatch(string st1, string st2){
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
