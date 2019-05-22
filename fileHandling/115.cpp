#include <fstream>
#include <iostream>

using namespace std;

int main(){
	fstream file("115.txt", ios :: in | ios :: out | ios :: app);

	if(!file.is_open()){
		cout << "lol";
	}else{
		cout << "file opened successfully" << endl;
		cout << "writting to the file" << endl;

		// n x executing this program appends this string below
		// n x into the file. Example: n = 3 for file << "yolo\n";
		// the file with have 
							//yolo
							//yolo
							//yolo
		file << "jizz jizz in my pants<=========3" << endl;
		file.seekg(0);	//have our file pointer look at the first character in the file. 
						//it wont modify the file, were only using it for the while loop to store content 
						//for the sting below. 
		cout << "ready from the file" << endl;
		string line;
		while(file.good()) {
			getline(file, line);
			cout << line << endl;
		}
	}return 0;
}