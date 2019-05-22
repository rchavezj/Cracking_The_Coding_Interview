#ifndef TREE
#define TREE

#include <map>

using namespace std;

struct trinode{
	bool isCompleteWord;
	map<char, trinode*> childeren;
	trinode(){}
};

class tree{
	private:
		trinode* root;
	public:
		tree();
		trinode* Root(){ return root; };
		void insert(trinode* root, string str);
		void deleteTrieNode(trinode* root, string str);
		bool search(trinode* root, string str);
		bool startsWith(trinode* root, string prefix);
};

#endif