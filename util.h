time_t currentTime(){
        time_t curTime;
        time(&curTime);
        return curTime + TIMEZONE * 60 * 60;
}

int StringToNum(string s){
  int ans = 0;
  for (unsigned i=0; i < s.size(); i++){
    if (s[i] >= 48 && s[i] <= 57)
      ans = ans*10 + ((int) s[i]) - 48;
    else
      throw EXCEPTION_NOT_A_NUMBER;
  }
  return ans;
}

	bool vv(int i, int j){
		return (i<0 || j<0);
	}
	
	bool tryMatch(string st1, string st2){
		vector< vector<bool> > match(st1.length());
		for (int i=0;i<st1.length();i++){
			for (int j=0;j<st2.length();j++){
				if (st2[j] == '*') match[i].push_back(vv(i-1,j) || match[i - 1][j]); else
				if (st2[j] == '?') match[i].push_back(vv(i-1,j-1) || match[i - 1][j - 1]); else
				if (st2[j] == st1[i]) match[i].push_back(vv(i-1,j-1) ||  match[i - 1][j - 1]); else
					match[i].push_back(false);
			}
		}
		return match[st1.length()-1][st2.length()-1];
	}
