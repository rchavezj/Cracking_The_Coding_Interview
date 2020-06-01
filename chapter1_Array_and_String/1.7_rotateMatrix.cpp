#include <vector>
#include <string>
#include <iostream>

using namespace std;

// vector<vector<int> > rotateMatrix(vector<vector<int>> initialMatrix, int n){
// 	vector<vector<int> > rotatedMatrix = {};
	// for (int i = 0; i < n; ++i){
	// 	for (int j = 0; j < n; ++j){
	// 		rotatedMatrix[i][j] = initialMatrix[j][n - i - 1];
	// 	}
	// }
// 	return rotatedMatrix;
// }


int main (){

	int n = 4;
	vector<vector<int> > initialMatrix;
	//vector<vector<int> > rotatedMatrix;
	initialMatrix = {
        {1,2,3,4},  
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}};

    //matrix without rotation
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n ; ++j){
            cout << initialMatrix[i][j] << "  ";
        }
        cout << endl;
    }

    cout << "\n";

    //90 degrees clockwise
	for (int i = 0; i < n; ++i){
		for (int j = n-1; j > -1 ; --j){
			cout << initialMatrix[j][i]<< "  ";
		}
        cout << endl;
	}

    cout << "\n";

    //90 degrees counter clockwise
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n ; ++j){
            cout << initialMatrix[j][n - i - 1]<< "  ";
        }
        cout << endl;
    }

    cout << "\n";

    //180 degrees counter clockwise
    for(int i = n-1; i > -1 ; --i){
        for(int j = n-1; j > -1 ; --j){
            cout << initialMatrix[i][j]<< "  ";
        }
        cout << endl;
    }



}


