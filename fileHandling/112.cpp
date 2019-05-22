#include <fstream>
#include <iostream>

using namespace std;

int main(){
	fstream file;

	file.open("112.txt", ios :: in | ios :: out | ios :: trunc);

	if(!file.is_open()){
		cout << "Error! Trying to open a file" << endl;
	}else{
		//this is where we can open a file. 
		cout << "file either exist or trunctify bitch." << endl;
		file.close();
	}
}