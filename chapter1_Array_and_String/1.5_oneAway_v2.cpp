#include <string>
#include <iostream>
#include "1.5_oneAway_v2.h"
using namespace std;

bool oneAwayProblem::oneAway(string one, string two){

	if(one.length() == two.length()){
		return oneReplacementAway(one, two);
	}

	else if(one.length() == two.length() - 1){
		return oneEditAway(one, two);
	}

	else if(two.length() == one.length() -1){
		return oneEditAway(two, one);
	}

	return false;
}

bool oneAwayProblem::oneReplacementAway(string one, string two){
	int testFailed = 0;
	for (int i = 0; i < one.size(); i++){
		if(one[i] != two[i]){
			testFailed++;
			if (testFailed > 1){
				return false;
			}
		}
	}return true;
}

bool oneAwayProblem::oneEditAway(string smallStr, string bigStr){
	int testFailed = 0;
	int bigStrItor = 0;
	int smallStrItor = 0;
	for (; smallStrItor < smallStr.size(); smallStrItor++, bigStrItor++){
		if(smallStr[smallStrItor] != bigStr[bigStrItor]){
			testFailed++;
			if (testFailed > 1){
				return false;
			}
			bigStrItor++;
		}
	}return true;
}

int main (){
	oneAwayProblem yo;

	printf("%s\n", yo.oneAway("pale", "ple") ? "True" : "False");
	printf("%s\n", yo.oneAway("palese", "pale") ? "True" : "False");
	printf("%s\n", yo.oneAway("pale", "bale") ? "True" : "False");
	printf("%s\n", yo.oneAway("pale", "bake") ? "True" : "False");
	

}

