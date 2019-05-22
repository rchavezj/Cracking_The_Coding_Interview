#include <iostream>
#include <vector>
#include <limits>		// numeric_limits<int>::max();
#include <algorithm>    // std::max
#include <tuple>

using namespace std;

int maxProfit(vector<int> stockPrices, int cooldown){
	int profit = 0;

	for(int i = 1; i < stockPrices.size(); i++){
		if(i == 1){
			if(stockPrices[i] < stockPrices[i+1]){
				profit += stockPrices[i+1] - stockPrices[i];
			}
		}else{
			if (cooldown == 0){
				if(stockPrices[i] < stockPrices[i+1]){
					profit += stockPrices[i+1] - stockPrices[i];
					cooldown++;
				}
			}else{
				profit += 0;
				cooldown--;
			}
		}
	}
	return profit;
}


int main (){
	vector <int>stockPrices = {1, 2, 3, 0, 2};

	int stockOptions = maxProfit(stockPrices, 1);

	cout << stockOptions << endl;

	cout << endl;

}