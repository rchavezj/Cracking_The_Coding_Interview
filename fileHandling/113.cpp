#include <fstream>
#include <iostream>

using namespace std;

int main (){
	ofstream file("113.txt");

	if(!file.is_open()){
		cout << "enable to find the file" << endl;
	}else{
		file << "I like licking sweaty balls" << endl;
		file << "yolo" << endl;
		cout << "done wrting content to the file" << endl;
		file.close();
		
	}
	return 0;
}