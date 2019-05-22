 #include <map>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main(){
	fstream file("slimShadyKimSong.txt");
	ofstream outFile("censoredSong.txt", ios::in | ios::out | ios::trunc);

	outFile << "yolo" << endl;

	if(!file.is_open()){
		cout << "error opening the file";
	}else{
		string word;
		string fileStr;
		map<string, bool> badWords;
		badWords["bitch"] = true;
		while(file.good()) {
		    getline(file, fileStr);
		    for (int i = 0; i < fileStr.size(); ++i){
				if((fileStr[i] != ' ') && (fileStr[i] != ',') && (fileStr[i+1] != '\n')  && (fileStr[i] != '.')  && (fileStr[i] != '?')){
					word.insert(word.end(), fileStr[i]);
				}else{
					cout << word << endl;
					cout << endl;
					if(badWords[word] == true){
						auto beginRange = i - word.size();
						auto endRange = i - 1;
						for (int j = beginRange; j <= endRange; ++j){
							fileStr[j] = '*';
						}
					}word.erase(word.begin(), word.end());
				}
			}
			outFile << fileStr << endl;
			fileStr.erase(fileStr.begin(), fileStr.end());
		}
	}
}