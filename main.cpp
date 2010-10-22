/* Author: He Haocong */
#include "includes.h"
#include "cleanUp.cpp"
#include "init.h"

int main(int argc, char* argv[]){
    init();
    shell->start();
    cleanUp();
	return 0;
}
