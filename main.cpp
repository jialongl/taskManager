/* Author: He Haocong */
#include "includes.h"

int main(int argc, char* argv[]){
	init();
	cronManager->newTasks(cronManager->lastTime, currentTime());
    Shell::start();
	return 1;
}
