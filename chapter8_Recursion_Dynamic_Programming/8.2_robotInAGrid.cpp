#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class robotInAGrid{
	public:
		int countPaths(vector<vector<bool>> grid, int row, int col){
			if(!validSquare(grid, row, col)) return 0;
			if(atEnd(grid, row, col)) return 1;
			cout << "row: " << row << endl;
			cout << "col: " << col << endl;
			cout << endl;
			return countPaths(grid, row+1, col) + countPaths(grid, row, col+1);
		}

		int countPaths(vector<vector<bool>> grid, int row, int col, vector<vector<int>> paths){
			if(!validSquare(grid, row, col)) return 0;
			if(atEnd(grid, row, col)) return 1;
			if(paths[row][col] == 0){
				paths[row][col] =  countPaths(grid, row+1, col) + countPaths(grid, row, col+1);
			}
			return paths[row][col];
		}

		bool atEnd(vector<vector<bool>> grid, int row, int col){
			if ((grid[row][col]) && (row == grid.size()-1) && (col == grid[0].size()-1)){return true;}
			return false;
		}

		bool validSquare(vector<vector<bool>> grid, int row, int col){
			if((0 <= row) && (row < grid.size()) && (0 <= col) && (col < grid[0].size()) ){
				if (grid[row][col]){return true;}
			}
			return false;
		}
};

vector<vector<int>> path(5, vector <int> (5, 0) );

vector<vector<bool>> grid(5, vector <bool> (5, true) );

int main(){


	 grid[0][1] = false;
	 grid[2][1] = false;
	 grid[3][1] = false;
	 grid[4][1] = false;

	 grid[2][2] = false;
	 grid[3][2] = false;
	 grid[4][2] = false;
	 grid[1][3] = false;
	 grid[3][4] = false;


	cout << "Grid maze:" << endl;
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[i].size(); j++){
			cout << grid[i][j];
			if (j == grid[i].size()-1){
				cout << endl;
			}
		}
	}
	cout << endl;

	robotInAGrid robotObj;

	cout << robotObj.countPaths(grid, 0, 0, path) << endl;



	return 0;
}




