#include <string>
#include <iostream>
#include "1.5_oneAway_v1.h"
using namespace std;

bool oneAwayProblem::oneAway(string one, string two){
	int edits = 0;

	if(one.length() == two.length()){
		return oneReplacementAway(one, two, edits);
	}

	else if(one.length() == two.length() + 1){
		return oneEditAway(one, two, edits);
	}

	else if(one.length() - 1 == two.length()){
		return oneEditAway(two, one, edits);
	}

	return false;
}

bool oneAwayProblem::oneReplacementAway(string one, string two, int edits){
	for(int str = 0; str < one.size(); str++){
		if(one[str] != two[str]){
			edits++;
			if(edits > 1){
				return false;
			}
		}
	}return true;
}

bool oneAwayProblem::oneEditAway(string one, string two, int edits){
	if(edits > 1){
		return false;
	}else{
		int firstIndex = 0;
		if(two[firstIndex] == one[firstIndex]){
			if((one.length() == 0) && (two.length() == 0)){
				return true;
			}
			return oneEditAway(one.erase(firstIndex,1), two.erase(firstIndex,1), edits);
		}else{
			if(two[firstIndex] == one[firstIndex+1]){
				return oneEditAway(one.erase(firstIndex,2), two.erase(firstIndex,1), edits + 1);
			}else{
				return false;
			}
		}
	}
}

int main (){
	oneAwayProblem yo;

	printf("%s\n", yo.oneAway("pale", "ple") ? "True" : "False");
	printf("%s\n", yo.oneAway("palese", "pale") ? "True" : "False");
	printf("%s\n", yo.oneAway("pale", "bale") ? "True" : "False");
	printf("%s\n", yo.oneAway("pale", "bake") ? "True" : "False");
	

}

