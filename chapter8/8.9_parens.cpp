#include <iostream>

using namespace std;


class parens{
	public:
		void initialParen(int numberOfCombinations){
			if(numberOfCombinations > 0){
				combinationalParenthesis(numberOfCombinations-1, numberOfCombinations, "(");
			}else{
				cout << "The input is not valid for a combination" << endl;
			}
		}

		void combinationalParenthesis(int openParen, int closeParen, string str){
			if((openParen == 0) && (closeParen == 0)){
				cout << str << endl;
				return;
			}

			if(openParen > closeParen){
				return;
			}

			if(openParen > 0){
				combinationalParenthesis(openParen-1, closeParen, str + "(");
			}

			if(closeParen > 0){
				combinationalParenthesis(openParen, closeParen-1, str + ")");
			}
		}
};


int main (){
	parens parensObj;

	int n = 0;

	parensObj.initialParen(n);
}






