#include <vector>
#include <iostream>

using namespace std;

vector<int> pastQueensRow;
vector<int> pastQueensCol;

vector<vector<bool>> chessBoard(4, vector<bool> (4, true));

class Queens{
	public:

		void printNQueens(int n){
			if (nQueens(0)){
				for (int i = 0; i < chessBoard.size(); i++){
					for (int j = 0; j < chessBoard[i].size(); j++){
						cout << chessBoard[i][j];
					}
					cout << endl;
				}
			}
		}

		void setQueueTerritory(int row, int col, int _value){
			int diagRow = 0, diagCol = 0;
			int diagzRow = 0, diagzCol = 0;

			if(row > col){diagRow = row - col; diagCol = 0;}
			else if(row == col){diagRow = diagCol = 0;}
			else{diagCol = col - row; diagRow = 0;}

			int maxDimension = row + col;
			if(maxDimension < chessBoard.size()){
				diagzRow = 0;
				diagzCol = maxDimension;
			}else{
				diagzRow = maxDimension - chessBoard.size() + 1;
				diagzCol = chessBoard.size() - 1;
			}
			for (int i = 0; i < chessBoard.size(); i++){
				//row of a queen
				if (i != row){ chessBoard[i][col] = _value; }
				//column of a queen 
				if (i != col){ chessBoard[row][i] = _value; }
			}

			int diagSize = 0;
			if(diagRow == 0){diagSize = chessBoard.size() - diagCol;}
			else{diagSize = chessBoard.size() - diagRow;}
			for(int i = 0; i < diagSize; i++){
				//back slash diagonal 
				if(diagRow+i != row && diagCol+i != col){
					chessBoard[diagRow+i][diagCol+i] = _value;
				}
			}

			int diagzSize = 0;
			if(diagzRow == 0){diagzSize = diagzCol + 1;}
			else{diagzSize = chessBoard.size() - diagzRow;}
			for(int i = 0; i < diagzSize; i++){
				//forward diagonal
				if(diagzRow+i != row && diagzCol-i != col){
					chessBoard[diagzRow+i][diagzCol-i] = _value;
				}
			}
		}

		//assume if the first row can 
		//start iterating at the second column of the chess table. 
		bool nQueens(int depth){
			int i = 0;
			bool newQueen = false;
			if (depth == 0)
			{
				i = 1;
			}
			for (; i < chessBoard.size(); i++){
				if(chessBoard[depth][i] == 1){
					if (depth == chessBoard.size()-1){ return true; }
					setQueueTerritory(depth, i, 0);
					pastQueensRow.push_back(depth);
					pastQueensCol.push_back(i);
					newQueen = nQueens(depth+1);

					if(!newQueen){
						// cout << "size: " << pastQueensRow.size() << endl;
						for(int yolo = pastQueensRow.size()-1; yolo > 0; yolo--){
							cout << pastQueensRow[yolo] << endl;
							cout << pastQueensCol[yolo] << endl;
							cout << endl;
							if(yolo == pastQueensRow.size()-1){
								setQueueTerritory(pastQueensRow[yolo], pastQueensCol[yolo], 1);
							} 
							setQueueTerritory(pastQueensRow[yolo], pastQueensCol[yolo], 0);
						}
						pastQueensRow.pop_back();
						pastQueensCol.pop_back();
					}
					else{return true;}
				}
			}return true;
		}
};

int main(){
	Queens queen;

	for(int i = 0; i < chessBoard.size(); i++){
		for(int j = 0; j < chessBoard[i].size(); j++){
			cout << chessBoard[i][j];
		}cout << endl;
	}
	cout << endl;

	queen.printNQueens(4);
}






