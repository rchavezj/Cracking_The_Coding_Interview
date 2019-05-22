#include <iostream>

using namespace std;

string URLify(string inputString, int adjustedLength){
	int space = 0;
	string outputString;
	for(int i = 0; i < adjustedLength; i++){
		int offset = 2 * space;
		if(inputString[i] == ' '){
			outputString[i + offset] = '%';
			outputString[i + offset + 1] = '2';
			outputString[i + offset + 2] = '0';
			space++;
		}else{
			outputString[i + offset] = inputString[i];
		}
	}
	return outputString;
}


int main (){
	string input = "Mr John Smith      y   k         j ";

	int newAdjustedLength = 35;

	string output = URLify(input, newAdjustedLength);

	cout << "Output is (" << output.c_str() << ")." << endl;
}
