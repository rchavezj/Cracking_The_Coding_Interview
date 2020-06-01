#include <iostream>

using namespace std;

string URLify(string inputString, int adjustedLength){
	string outputString;
	for (int i = 0; i < adjustedLength; i++){
		if(inputString.at(i) == ' '){
			outputString.insert(outputString.end(), '%');
			outputString.insert(outputString.end(), '2');
			outputString.insert(outputString.end(), '0');
		}else{
			outputString.insert(outputString.end(), inputString.at(i));
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
