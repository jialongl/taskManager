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
