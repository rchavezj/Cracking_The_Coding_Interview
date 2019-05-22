#include <map>
#include <string>

using namespace std;

bool palindromePermutation(string word){
	int count = 0;
	map <char,bool> dict;
	for (auto _char : word){
		if(int(_char) > 96  && int(_char) < 123){
			dict[_char] =  (!dict[_char]);
		}
	}
											//	map<char, bool>::iterator value;
	for(auto value : dict){					//  for(value = dict.begin(); value != dict.end(); value++){
		if(value.second == true){			// 	if(value->second == true){
			count += 1;
			if(count > 1){
				return false;
			}
		}
	}
	return true;
}

int main (){
	printf("%s\n", palindromePermutation("aabidd") ? "True" : "False");
	printf("%s\n", palindromePermutation("aea") ? "True" : "False");
	printf("%s\n", palindromePermutation("rats live on no evil star") ? "True" : "False");
}
