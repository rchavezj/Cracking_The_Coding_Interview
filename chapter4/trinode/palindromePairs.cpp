#include <map>
#include <iostream>
#include "trieList.h"

using namespace std;

// tree constructor
tree::tree(){
    root = new trienode(); // set head to NULL
}

void tree::insert(trienode* root, string str, int index){
	trienode* cursor = root;
	for (int i = str.size()-1; i > 0; i--){
		trienode* node = cursor->childeren[str[i]];
		if (node == NULL){
			node = new trienode();
			node->parent = str[i];
			cursor->childeren[str[i]] = node;
		}cursor->list.push_back(index);
		cursor = node;
	}cursor->index = index;
}

int pairIndex = 0;
void tree::search(trienode* root, vector< vector<int> > pairs, vector<string> words, string word, int index){
	string subStr;
	trienode* cursor = root;
	for (int i = 0; i < word.size(); i++){
		trienode* node = cursor->childeren[i];
		if(cursor == NULL && 
		int(word[i]) > 96 && 
		int(word[i]) < 123){
			return;
		}
		if(word[i] != node->parent){ return; }
		cursor = node;
	}
	if(cursor->index != -1){
		pairs[pairIndex].push_back(index);
		pairs[pairIndex].push_back(cursor->index);
		pairIndex++;
	}
	if(cursor->list.size() > 1){
		for (int i = 0; i < cursor->list.size(); i++){
			if (cursor->list[i] != index){
				subStr.insert(0, words[i], 0, words[i].size() - word.size());  		   
				if(isPalindrome(subStr)){
					pairs[pairIndex].push_back(index);
					pairs[pairIndex].push_back(i);
					pairIndex++;
				}
				subStr.clear();
			}
		}
	}return;
}

bool tree::isPalindrome(string s){
  int n = s.size();
  for (int i = 0; i < (n/2); i++) {
     if(s[i] != s[n - i - 1]) {
         return false;
     }
  }
  return true;
}

vector< vector<int> > tree::palindromePair(trienode* root, vector<string> str){
	vector< vector<int> > list;
	for (int i = 0; i < str.size(); i++){ insert(root, str[i], i); }
	for (int i = 0; i < str.size(); i++){ search(root, list, str, str[i], i); } 
	return list;
}



int main (){

}









