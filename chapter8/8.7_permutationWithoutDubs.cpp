#include <map>
#include <tuple>
#include <vector>
#include <iostream>

using namespace std;

class stringPermutation{

	public:
		tuple<map<char, int>, int, bool> repitiveCharacters(string word){
			int totalChar;
			map<char,int> dict;
			for(auto _char : word){
				totalChar++;
				dict[_char]++;
			}
			for(auto _dict : dict){
				if(_dict.second > 1){
					return make_tuple(dict, totalChar, false);
				}
			}

			return make_tuple(dict, totalChar, true);
		}

		void permuateWithoutDubs(map<char, int> dict, vector<char> result, int depth){
			if(depth == result.size()){
				string str(result.begin(),result.end());
				cout << str << endl;
			}else{
				for(auto _dict : dict){
					if(_dict.second != 0){
						dict[_dict.first]--;
						result[depth] = _dict.first;
						permuateWithoutDubs(dict, result, depth+1);
						dict[_dict.first]++;
					}
				}
			}
		}
};




int main (){
	string word = "ABC";

	stringPermutation permutate;

	tuple<map<char, int>, int, bool> permuation = permutate.repitiveCharacters(word);	

	for (auto index : get<0>(permuation)){
		cout << "key: " << index.first << endl;
		cout << "value: " << index.second << endl;
		cout << endl;
	}

	bool uniqueCharacters = get<2>(permuation);

	if(uniqueCharacters){

		map<char, int> dict = get<0>(permuation);

		int totalChar = get<1>(permuation);

		vector<char> result(totalChar);

		permutate.permuateWithoutDubs(dict, result, 0);

	}else{

		cout << "The string is not unieue!" << endl;
	
	}
}

