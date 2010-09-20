#include<iostream>
#include<fstream>
using namespace std;
int main(){
	ifstream fin("record.xml");
	char cstr[256];
	fin.getline(cstr,256);
	cout<<string(cstr);
	
}
