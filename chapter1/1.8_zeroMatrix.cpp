#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<vector<int> > zeroMatrix(vector<vector<int>> initialMatrix){
	int rowLength = initialMatrix.size();
	int columnLength = initialMatrix[0].size();		//assuming we have M columns for each N row
	vector<vector<int>> newMatrix = initialMatrix;
	vector<int> indexReference;
	for (int i = 0; i < rowLength; ++i){
		for (int j = 0; j < columnLength; ++j){
			if(newMatrix[i][j] == 0){
				indexReference.push_back(i);
				indexReference.push_back(j);
			}
		}
	}
	for (int i = 0; i < indexReference.size(); i += 2){
		int row = indexReference[i];
		int column = indexReference[i+1];
		for(int m = 0; m < rowLength; m++){
			if(m == row){
				for(int iterateCol = 0; iterateCol < columnLength; iterateCol++){
					newMatrix[m][iterateCol] = 0;
				}
			}
			for(int n = 0; n < columnLength; n++){
				if(n == column){
					for(int iterateRow = 0; iterateRow < rowLength; iterateRow++){
						newMatrix[iterateRow][n] = 0;
					}
				}
			 }
		}
	}
	return newMatrix;
}



int main(){
	vector<vector<int> > initialMatrix;
	initialMatrix = {
        {1,    2,   3,   4},  
        {5,    0,   7,   8},
        {9,   10,  11,  12},
        {13,  14,   0,  16},
    	{17,  18,  19,  20}};

   vector<vector<int>> newMatrix = zeroMatrix(initialMatrix);

	for(int i = 0; i < newMatrix.size(); ++i){
		for(int j = 0; j < newMatrix[i].size(); j++){
			cout << newMatrix[i][j] << "    ";
		}
		cout << "\n";
	}
}








