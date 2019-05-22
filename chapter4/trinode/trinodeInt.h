#ifndef TREE
#define TREE

#include <map>
#include <vector>

using namespace std;

struct trinode{
	bool isCompleteWord;
	map<int, trinode*> childeren;
	trinode(){}
};

class tree{
	private:
		trinode* root;
	public:
		tree();
		trinode* Root(){ return root; };
		void insert(trinode* root, vector<int> str);
		void deleteTrieNode(trinode* root, vector<int> str);
		bool search(trinode* root, vector<int> str);
		bool startsWith(trinode* root, vector<int> prefix);
		int noInitialParent(trinode* root, vector<vector<int>> paths);
		int longestConsecutivePath(trinode* parent, trinode* root, vector<vector<int>> paths, int length);
};

#endif