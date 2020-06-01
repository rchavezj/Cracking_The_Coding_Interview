#include "BSTree.h"
#include <iostream>
#include <iomanip>		// std::setw
#include <cmath> 		//#define INFINITY /*implementation defined*/

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

void BSTree::Insert(BSTNode *& root, int item){
	BSTNode* newNode = new BSTNode();
	newNode->data = item;
	if (root == NULL){ root = newNode; return; }
	BSTNode* parent = NULL;
	BSTNode* cursor = root;
	while(cursor != NULL) {
	    parent = cursor;
	    if (item <= cursor->data){
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

bool BSTree::validateBST(BSTNode *& root, int min, int max){
	if(root == NULL){ return true; }
	if (max < root->data && root->data <= min){return false;}
	bool validateLeftSub = validateBST(root->left, min, root->data);
	bool validateRightSub = validateBST(root->right, root->data, max);
	return validateLeftSub && validateRightSub;
}

int main (){
	BSTree tree;
	BSTNode* root = tree.Root();
	tree.Insert(root, 5);
	tree.Insert(root, 3);
	tree.Insert(root, 4);
	tree.Insert(root, 1);
	tree.Insert(root, 2);
	tree.Insert(root, 7);
	tree.Insert(root, 6);
	tree.Insert(root, 8);
	tree.print(root, 0);
	bool validateBSTFunc = tree.validateBST(root, -INFINITY, INFINITY);
	if (validateBSTFunc){
		cout << "tree if valid" << endl;
	}else{
		cout << "tree is not valid" << endl;
	}
}



