#include<iostream>
#include<fstream>
using namespace std;
int main(){
	ifstream fin("object");
	char cstr[256];
	fin.getline(cstr,256);
	cout<<string(cstr);
	
}
