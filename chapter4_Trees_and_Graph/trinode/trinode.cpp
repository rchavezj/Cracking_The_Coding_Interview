#include <map>
#include <iostream>
#include "trinode.h"

using namespace std;


// tree constructor
tree::tree(){
    root = new trinode(); // set head to NULL
}

void tree::insert(trinode* root, string str){
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


void tree::deleteTrieNode(trinode* root, string str){
	char key;
	if (int(str[0]) > 96 && int(str[0]) < 123 && str.size() > 0){
		key = str[0];
	}
	trinode* parent = NULL;
	trinode* cursor = root;
	for (int i = 0; i < str.size(); i++){
		trinode* node = cursor->childeren[str[i]];
		// for (auto value : cursor->childeren){
		// 	cout << i << endl;
		// 	cout << value.first << endl;
		// 	cout << endl;
		// }
		if(cursor == NULL && cursor->childeren.find(str[i]) == cursor->childeren.end()){
			//cout << "string doesn't exist inside the trie" << endl;
			return;	
		}
		if(cursor->isCompleteWord || cursor->childeren.size() > 1){
			parent = cursor;
			key = str[i];
		}
		if (i == str.size() - 1 ){
			cursor = node;
			if(cursor->isCompleteWord && cursor->childeren.size() > 0){
				//cout << "sub word deleted" << endl;
				//cout << endl;
				cursor->isCompleteWord = false;
				return;
			}
		}
		cursor = node;
	}
	if (parent != NULL){
		if(cursor->isCompleteWord && cursor->childeren.size() == 0){
			//cout << "cut off part of a prefix" << endl;
			parent->childeren.erase(key);
		}
	}else{
		//cout << "whole word deleted from root! " << endl;
		root->childeren.erase(key);
	}
}



bool tree::startsWith(trinode* root, string prefix){
	trinode* cursor = root;
	for (int i = 0; i < prefix.size(); i++){
		trinode* node = cursor->childeren[prefix[i]];
		if (node == NULL && cursor->childeren.find(prefix[i]) == cursor->childeren.end()){
			return false;
		}
		cursor = node;
	}return true;
}

bool tree::search(trinode* root, string str){
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
	string abc = "abc";
	string abgl = "abgl";
	string cdf = "cdf";
	string abcd = "abcd";
	string lmn = "lmn";
	treelist.insert(root, abc);
	treelist.insert(root, abgl);
	treelist.insert(root, abcd);
	treelist.insert(root, abcd);
	treelist.insert(root, lmn);
	treelist.insert(root, cdf);

	if (treelist.startsWith(root, "ab")){
		cout << "ab is a prefix in the tree" << endl;
	}else{
		cout << "ab is not a prefix of the tree" << endl;
	}

	if (treelist.search(root, "ab")){
		cout << "ab is a complete word in the tree" << endl;
	}else{
		cout << "ab is not complete word in the tree" << endl;
	}


	treelist.deleteTrieNode(root, abc);
	treelist.deleteTrieNode(root, abgl);
	treelist.deleteTrieNode(root, abcd);
}



