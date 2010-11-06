/* Author: He Haocong */
#include "Shell.h"

int main(int argc, char* argv[]){
    Shell* shell = new Shell();
    string args = flaten(argc,argv);
    shell->start(args);
    delete shell;
	return 0;
}
