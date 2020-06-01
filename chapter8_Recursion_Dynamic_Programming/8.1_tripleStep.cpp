#include <vector>
#include <iostream>

using namespace std;


unsigned int dynamicTripleSteps(int n){
	if (n <= 1){
		return n;
	}

	vector<int> table(n + 1);

	table[0] = table[1] = 1;

	for (int i = 2; i <= n; ++i) {
		table[i] = table[i-1] + table[i-2] + table[i-3];
	}    
	return table.back();
}

unsigned int memoizationTripleSteps(int n){

	if(n <= 1){
		return n;
	}

	static vector<int> table (n+1);

	if(table[n] == 0 ){
		table[n] = memoizationTripleSteps(n-1) + memoizationTripleSteps(n-2) + memoizationTripleSteps(n-3);
	}

	return table[n];
}





int main(){
	cout << dynamicTripleSteps(6) << endl;
	cout << memoizationTripleSteps(6) << endl;
}