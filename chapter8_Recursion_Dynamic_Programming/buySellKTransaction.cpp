#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


vector<vector<int>> maxProfit(vector<int>stock, int transaction){

	vector<vector<int>> table(transaction+1, vector <int> (stock.size(), 0) );

	for(int i = 1; i < table.size(); i++){
		int maxDifference = -stock[0];
		for (int j = 1; j < table[i].size(); j++){
			table[i][j] = max(table[i][j-1], stock[j] + maxDifference);
			maxDifference = max(maxDifference, table[i-1][j] - stock[j]);
		}
	}return table;
}


int main(){
	int transaction = 3;

	vector<int> stock = {2, 5, 7, 1, 4, 3, 1, 3};

	vector<vector<int>> input = maxProfit(stock, transaction);

	for(int i = 0; i < input.size(); i++){
		for (int j = 0; j < input[i].size(); j++){
			cout << input[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}





