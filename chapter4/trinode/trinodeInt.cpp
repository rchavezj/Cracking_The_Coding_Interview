#include <map>
#include <iostream>
#include "trinodeInt.h"

using namespace std;


// tree constructor
tree::tree(){
    root = new trinode(); // set head to NULL
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


void tree::deleteTrieNode(trinode* root, vector<int> str){
	int key;
	if (str.size() > 0){
		key = str[0];
	}
	trinode* parent = NULL;
	trinode* cursor = root;
	for (int i = 0; i < str.size(); i++){
		trinode* node = cursor->childeren[str[i]];
		if(cursor == NULL && cursor->childeren.find(str[i]) != cursor->childeren.end()){
			return;	
		}
		if(cursor->isCompleteWord || cursor->childeren.size() > 1){
			parent = cursor;
			key = str[i];
		}
		if (i == str.size() - 1 ){
			cursor = node;
			if(cursor->isCompleteWord && cursor->childeren.size() > 0){
				cursor->isCompleteWord = false;
				return;
			}
		}
		cursor = node;
	}
	if (parent != NULL){
		if(cursor->isCompleteWord && cursor->childeren.size() == 0){
			parent->childeren.erase(key);
		}
	}else{
		root->childeren.erase(key);
	}
}



bool tree::startsWith(trinode* root, vector<int> prefix){
	trinode* cursor = root;
	for (int i = 0; i < prefix.size(); i++){
		trinode* node = cursor->childeren[prefix[i]];
		if (node == NULL && cursor->childeren.find(prefix[i]) == cursor->childeren.end()){
			return false;
		}
		cursor = node;
	}return true;
}

bool tree::search(trinode* root, vector<int> str){
	trinode* cursor = root;
	for (int i = 0; i < str.size(); i++){
		trinode* node = cursor->childeren[str[i]];
		if (node == NULL && cursor->childeren.find(str[i]) == cursor->childeren.end()){
			return false;
		}
		cursor = node;
	}
	if (cursor->isCompleteWord){
		return true;
	}return false;
}

int main(){
	tree treelist;
	trinode* root = treelist.Root();
	vector<int> first = {1, 2, 3, 4};
	vector<int> second = {1, 10, 11, 0};
	vector<int> third = {5, 0, 0, 0};
	vector<int> fourth = {6, 0, 0, 0};
	vector<vector<int>> paths = {  {1, 2, 3, 4},
								   {1, 10, 11, 0},
								   {5, 0, 0, 0},
								   {6, 0, 0, 0}
								};
	treelist.insert(root, first);
	treelist.insert(root, second);
	treelist.insert(root, third);

	if (treelist.startsWith(root, {1, 2, 3})){
		cout << "1,2,3 is a prefix in the tree" << endl;
	}else{
		cout << "1,2,3 is not a prefix of the tree" << endl;
	}

	if (treelist.search(root, {1, 2, 3})){
		cout << "1,2,3 is a complete word in the tree" << endl;
	}else{
		cout << "1,2,3 is not complete word in the tree" << endl;
	}


	treelist.deleteTrieNode(root, {1,2,3, 4});
	treelist.deleteTrieNode(root, {1,10,11});
	treelist.deleteTrieNode(root, {5});
}



