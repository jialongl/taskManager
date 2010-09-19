time_t currentTime(){
        time_t curTime;
        time(&curTime);
        return curTime + TIMEZONE * 60 * 60;
}


