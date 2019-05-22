#include "BSTree.h"
#include <iostream>
#include <iomanip>		// std::setw
#include <stdlib.h>     /* abs */

using namespace std;

// BSTree constructor
BSTree::BSTree(){
    length = 0;
    root = NULL; // set head to NULL
    //vector<LinkedList> vectorList;
}
// LinkedList constructor
LinkedList::LinkedList(){
    length = 0;
    head = tail = NULL; 
}
void BSTree::print(BSTNode*& root, int indent){
	if(root != NULL){
		if(root->right){
			print(root->right, indent+4);
		}
		if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (root->right) std::cout<<"  /\n" << std::setw(indent) << ' ';
		cout << root->data << endl;
		if(root->left){
			std::cout << std::setw(indent) << ' ' <<" \\\n";
			print(root->left, indent+4);
		}
	}
}

void BSTree::Insert(BSTNode*& root, int item){
	BSTNode* newNode = new BSTNode();
	newNode->data = item;
	if (root == NULL){ root = newNode; return; }
	BSTNode* parent = NULL;
	BSTNode* cursor = root;
	while(cursor != NULL) {
		parent = cursor;
	    if(item <= cursor->data){
	    	cursor = cursor->left;
	    }else{
	    	cursor = cursor->right;
	    }
	}
	if (item <= parent->data){
		parent->left = newNode;
	}else{
		parent->right = newNode;
	}
}


int BSTree::height(BSTNode*& root){
	if (root == NULL){return 0;}
	int lHeight = height(root->left);
	int rHeight = height(root->right);

	if (lHeight >= rHeight){
		return lHeight + 1;
 	}else{
 		return rHeight + 1;
 	}
}
bool BSTree::checkBalanced(BSTNode*& root){
	if (root == NULL){ return true; }

	int lHeight = height(root->left);
	int rHeight = height(root->right);
	bool checkLeftSub = checkBalanced(root->left);
	bool checkRightSub = checkBalanced(root->right);

	if (abs(lHeight - rHeight) <= 1
		&& checkLeftSub && checkRightSub)
	{return true;}

	return false;
}





int main(){
	BSTree tree;
	BSTNode* root = tree.Root();
	tree.Insert(root, 6);
	tree.Insert(root, 5);
	tree.Insert(root, 3);
	// tree.Insert(root, 4);
	// tree.Insert(root, 1);
	// tree.Insert(root, 2);
	tree.Insert(root, 7);
	tree.Insert(root, 8);
	tree.print(root, 0);

	cout << "This tree is ...";
	if(tree.checkBalanced(root)){
		cout << "BALANCED!" << endl;
	}else{
		cout << "NOT BALANCED!" << endl;
	}
}







