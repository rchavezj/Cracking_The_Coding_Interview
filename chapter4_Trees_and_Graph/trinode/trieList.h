#ifndef TREE
#define TREE

#include <map>
#include <vector>


using namespace std;

struct trienode{
	int index;
	char parent;
	vector<int> list;
	map<char, trienode*> childeren;
	trienode(){
		index = -1;
		parent = ' ';
	}
};

class tree{
	private:
		trienode* root;
	public:
		tree();
		bool isPalindrome(string s);
		trienode* Root(){ return root; };
		void insert(trienode* root, string str, int index);
		void search(trienode* root, vector<vector<int>> pairs, vector<string> words , string word, int index);
		vector< vector<int> > palindromePair(trienode* root, vector<string> str);
};

#endif