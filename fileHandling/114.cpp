#include <fstream>
#include <iostream>

using namespace std;

int main (){
	ifstream file("114.txt");

	if (!file.is_open())
	{
		cout << "couldn't open the file" << endl;
	}else{
		string line;
		while(file.good()) {
		    getline(file, line);
		    cout << line << endl;
		}
	}
	return 0;
}