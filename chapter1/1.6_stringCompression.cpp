#include <string>
#include <iostream>

using namespace std;

string stringCompression(string str){
	/* PRECONDITION */
	/* if the string is empty, there's no*/
	/* bother to do any implementations*/
	if(str.length() != 0){
		/*since the length isn't zero,
		 theres at least one charater*/
		int repeatCharacters = 1;
		//new character
		string compressedString = "";	
		for(int i = 0; i <= str.length(); i++){
			/* if we have the same character for the
			next index, increment */
			if(	(int(str[i]) > 64 && int(str[i]) < 91)
				|| (int(str[i]) > 96  && int(str[i]) < 123)
				|| (int(str[i+1]) > 64 && int(str[i + 1]) < 91)
				|| (int(str[i+1]) > 96 && int(str[i + 1]) < 123)
			){
				if(str[i] == str[i+1]){
					repeatCharacters++;
				}else{
					/* if we have a different character, 
					then place repeatCharacters into the new string */
					compressedString.append(1, str[i]);
					compressedString.append(to_string(repeatCharacters));
					repeatCharacters = 1;
				}
			}
		}
		if(str.length() <= compressedString.length() ){
			return str;
		}
		else{
			return compressedString;
		}
	}return "Empty String";
}

int main (){
	printf("%s\n", stringCompression("abccccggGGccccccaba").c_str());	
}




