/* Author: He Haocong */
#include "Shell.h"

int main(int argc, char* argv[]){
    Shell* shell = new Shell();
    shell->start();
    delete shell;
	return 0;
}
