#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

bool hasPairWithSum(vector<int> data, int sum){
	unordered_set<int> comp;
	for(auto value: data){
		if(comp.find(value) != comp.end()){
			return true;
		}
		comp.insert(sum-value);
	}
	return false;
}


int main (){
 	vector<int> data1;	//= [1, 2, 3, 9]
 	data1.push_back(1);
 	data1.push_back(2);
 	data1.push_back(3);
 	data1.push_back(9);
	vector<int> data2;	//= [1, 2, 4, 4]
	data2.push_back(1);
	data2.push_back(2);
	data2.push_back(4);
	data2.push_back(4);

	if(hasPairWithSum(data1, 8)){
		cout << "data1 is a summation" << endl;
	}else{
		cout << "data1 is NOT have a summation" << endl;
	}

	if(hasPairWithSum(data2, 8)){
		cout << "data2 is a summation" << endl;
	}else{
		cout << "data2 is NOT have a summation" << endl;
	}
}