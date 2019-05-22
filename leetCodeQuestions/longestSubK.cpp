#include <map>
#include <iostream>
#include <unordered_map>

using namespace std;

int longestSubK(string str, int k){
	int sum = 0;
	map<char,bool> dict;
	int longestSubLen = 0;
	int lastCharSum = 0;
	for (int i = 0; i < str.size(); i++){
		if(int(str[i]) > 96  && int(str[i]) < 123){
			sum++;
			dict[str[i]] = true;
			if (dict.size() == k){
				if (dict[str[i+1]] == false){
					longestSubLen = max(longestSubLen, sum);
					sum = lastCharSum;
					dict.clear();
					dict[str[i]] = true;
				}
			}
			if(str[i] == str[i+1]){lastCharSum++;}
			else{lastCharSum = 1;}
		}else{sum = 0;}
	}return longestSubLen;
}


int main(){
	// k = 2, sub T = jujjuj, length = 6
	string subStr = "44ebbf55bggbgijujjuj4jjbkbj55bfgbbba";
	cout << longestSubK(subStr, 2) << endl;
}





