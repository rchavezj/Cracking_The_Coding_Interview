#include <iostream>

using namespace std;


bool checkPermutation(string s, string t){
	if(s.length() != t.length()){
		return false;
	}
	//auto = string::iterator
	for(int i = 0; i < s.length(); i++){
		for(int j = 0; j < t.length(); j++){
			if(s[i] == t[j]){
				t.erase(j, 1);
				break;
			}
		}
	}if(t.length() == 0){
		return true;
	}else{
		return false;
	}
}

int main (){
	string s = "abcd";
	string t = "abcd";
	string z = "abee";
	string q = "dcba";

	if(checkPermutation(s, t) == true){
		cout << "we have a permutation for " << s << " and " << t << "\n" << endl;
	}else{
		cout << "no permutation for " << s << " and " << t << "\n" << endl;
	}


	if(checkPermutation(s, z) == true){
		cout << "we have a permutation for " << s << " and " << z << "\n" << endl;
	}else{
		cout << "no permutation for " << s << " and " << z << "\n" << endl;
	}


	if(checkPermutation(s, q) == true){
		cout << "we have a permutation for " << s << " and " << q << "\n" << endl;
	}else{
		cout << "no permutation for " << s << " and " << q << "\n" << endl;
	}
	return 0;
}




