#include <iostream>
#include <vector>
#include <algorithm>    // std::max
#include <tuple>

using namespace std;

tuple<int, int> maxProfit(vector<int> stockPrices){
	int profit = 0;
	int minimumProfit = INT_MAX;

	for(int i = 0; i < stockPrices.size(); i++){
		minimumProfit = min(minimumProfit, stockPrices[i]);
		profit = max(profit, stockPrices[i] - minimumProfit);
	}
	return make_tuple(profit, minimumProfit);
}


int main (){
	vector <int>stockPrices = {7, 1, 5, 3, 6, 4};

	tuple<int, int> stockOptions = maxProfit(stockPrices);

	cout << "profit: " << get<0>(stockOptions) << endl;

	cout << "minimumProfit: " << get<1>(stockOptions) << endl;
}