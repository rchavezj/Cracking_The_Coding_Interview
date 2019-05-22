#include <map>
#include <tuple>
#include <vector>
#include <iostream>

using namespace std;

class stringPermutation{

	public:
		tuple<map<char, int>, int> repitiveCharacters(string word){
			int totalChar;
			map<char,int> dict;
			for(auto _char : word){
				totalChar++;
				dict[_char]++;
			}
			return make_tuple(dict, totalChar);
		}

		void permuateWithDubs(map<char, int> dict, vector<char> result, int depth){
			if(depth == result.size()){
				string str(result.begin(),result.end());
				cout << str << endl;
			}else{
				for(auto _dict : dict){
					if(_dict.second != 0){
						dict[_dict.first]--;
						result[depth] = _dict.first;
						permuateWithDubs(dict, result, depth+1);
						dict[_dict.first]++;
					}
				}
			}
		}
};




int main (){
	string word = "AABC";

	stringPermutation permutate;

	tuple<map<char, int>, int> permuation = permutate.repitiveCharacters(word);	

	for (auto index : get<0>(permuation)){
		cout << "key: " << index.first << endl;
		cout << "value: " << index.second << endl;
		cout << endl;
	}

	map<char, int> dict = get<0>(permuation);

	int totalChar = get<1>(permuation);

	vector<char> result(totalChar);

	permutate.permuateWithDubs(dict, result, 0);

}

