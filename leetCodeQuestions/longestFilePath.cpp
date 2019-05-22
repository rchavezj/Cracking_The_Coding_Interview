#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int longestFilePath(string input){
	int counter = 0;
	int tabCounter = 0;
	int previousTabCounter = 0;
	int differentTabLength = 0;
	vector<int> countHistory;
	vector<int> finalCountPath;
	for(int i = 0; i < input.size(); i++){
		if(input[i] == '\n'){
			i++; tabCounter = 0;
			while(input[i] == '\t'){
			    tabCounter++;
			    i++;
			}
			if (tabCounter > previousTabCounter){
				counter++;//connect child dir/file
				previousTabCounter = tabCounter;
				//have history count 
				//paths before final count
				countHistory.push_back(counter);
			}
			else if(tabCounter == previousTabCounter){
				//pushing a file path count
				finalCountPath.push_back(counter);
				counter = countHistory.back();
			}
			else{
				differentTabLength = previousTabCounter - tabCounter;
				for (int i = 0; i < differentTabLength; ++i){
					countHistory.pop_back();
				}
				//pushing a file path count
				finalCountPath.push_back(counter);
				counter = countHistory.back();
				previousTabCounter = differentTabLength;
			}
		}
		counter++;
	}
	finalCountPath.push_back(counter);//pushing last file path count

	auto max = max_element(finalCountPath.begin(), finalCountPath.end());
	return *max;
}


int main(){
        string filePath = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";

       	cout << filePath << endl;
       	cout << endl;
    
        cout << longestFilePath(filePath) << endl;
    }
