#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class ratInAMazePuzzle{
	public:
		vector<vector<string>> displayPath;

		ratInAMazePuzzle(int N) : displayPath(N, vector <string> (N, "-")){}

		bool countPaths(vector<vector<bool>> grid, int row, int col, string direction){
			if(!validSquare(grid, row, col)) return 0;
			if(atEnd(grid, row, col)){
				displayPath[row][col] = "F "; 
				return true;
			}
			
			displayPath[row][col] = "X";

			if(direction == "down"){
				return countPaths(grid, row+1, col, "down") + countPaths(grid, row, col+1, "right") + countPaths(grid, row, col-1, "left");
			}
			if(direction == "right"){
				return countPaths(grid, row+1, col, "down") + countPaths(grid, row, col+1, "right") + countPaths(grid, row-1, col, "up");
			}
			if(direction == "up"){
				return countPaths(grid, row, col+1, "right") + countPaths(grid, row-1, col, "up") + countPaths(grid, row, col-1, "left");
			}
			if(direction == "left"){
				return countPaths(grid, row+1, col, "down") + countPaths(grid, row-1, col, "up") + countPaths(grid, row, col-1, "left");
			}
			return false;
		}





		int countPaths(vector<vector<bool>> grid, int row, int col, vector<vector<int>> paths){
			if(!validSquare(grid, row, col)) return 0;
			if(atEnd(grid, row, col)){
				displayPath[row][col] = "F"; 
				return 1;
			}
			displayPath[row][col] = "S";
			if(paths[row][col] == 0){
				paths[row][col] =  countPaths(grid, row+1, col, "down") + countPaths(grid, row, col+1, "right") + 
				countPaths(grid, row-1, col, "up") + countPaths(grid, row, col-1, "left");
			}
			printMaze(displayPath);
			return paths[row][col];
		}

		void printMaze(vector<vector<string>> paths){
			cout << "Rats path: " << endl;
			for(int i = 0; i < paths.size(); i++){
				for(int j = 0; j < paths[i].size(); j++){
					cout << paths[i][j];
					if (j == paths[i].size()-1){
						cout << endl;
					}
				}
			}cout << endl;
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
	 //grid[4][1] = false;

	 grid[2][2] = false;
	 grid[3][2] = false;
	 //grid[4][2] = false;
	 grid[1][3] = false;
	 grid[3][4] = false;
	 grid[1][4] = false;
	 //grid[4][4] = false;

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

	ratInAMazePuzzle robotObj(5);

	if(robotObj.countPaths(grid, 0, 0, path) != 0){
		cout << "The rat has found the destination!\n " << endl;
	}else{
		cout << "path not found!" << endl;
	}



	return 0;
}




