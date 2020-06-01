#include <iostream>
#include "trinodeInt.h"

using namespace std;


// tree constructor
tree::tree(){
    root = new trinode(); 
}

void tree::insert(trinode* root, vector<int> str){
	trinode* cursor = root;
	for (int i = 0; i < str.size(); i++){
		trinode* node = cursor->childeren[str[i]];
		if (node == NULL){
			node = new trinode();
			cursor->childeren[str[i]] = node;
		}
		cursor = node;
	}cursor->isCompleteWord = true;
}

int tree::noInitialParent(trinode* root, vector<vector<int>> paths){
	trinode* parent = NULL;
	return longestConsecutivePath(parent, root, paths, 0);
}

int tree::longestConsecutivePath(trinode* parent, trinode* root, vector<vector<int>> paths, int length){
	int maxLen = 0;
	trinode* cursor = root;
	for(int i = 0; i < paths.size(); i++){
		for(int j = 0; j < paths[i].size(); j++){
			trinode* node = cursor->childeren[paths[i][j]];
			//cout << paths[i][j] << endl;
			if(parent != NULL &&
				  cursor->childeren.find(paths[i][j]) !=  cursor->childeren.end() &&
				  parent->childeren.find(paths[i][j-1]) !=  cursor->childeren.end() &&
				  paths[i][j-1] + 1 == paths[i][j]
				 ){
					length++;
			}else{
				if(cursor->childeren.find(paths[i][j]) !=  cursor->childeren.end()){
					//cout << "daddy's not home yet: " << paths[i][j] << endl;
					length = 1;
				}
			}
			if (node != NULL){
				parent = cursor;
				cursor = node;
			}
			//cout << "length: " << length << endl;
		}
		maxLen = max(maxLen, length);
		//cout << "maxLen: " << maxLen << endl;
		length = 0;
		//cout << endl;
	}return maxLen;
}

int main(){
	tree treelist;
	trinode* root = treelist.Root();
	vector<int> first = {1, 2, 3, 4};
	vector<int> second = {1, 10, 11, 12};
	vector<int> third = {5, 0, 0, 0};
	vector<vector<int>> paths = {  {1, 2, 3, 4},
								   {1, 10, 11, 12},
								   {5, 6, 7, 8, 9, 10},
								   {6}
								};
	treelist.insert(root, first);
	treelist.insert(root, second);
	treelist.insert(root, third);

	cout << treelist.noInitialParent(root, paths) << endl;
}







