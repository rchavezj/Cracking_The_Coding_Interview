#include <tuple>
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
	if (parent->left == cursor){
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


BSTNode* BSTree::target(BSTNode*& root, int targetInt){
	if (root == NULL){ return NULL; }
	if(root->data == targetInt){return root;}
	else if(root->data > targetInt){return target(root->left, targetInt);}
	else{return target(root->right, targetInt);}
}


BSTNode* BSTree::firstCommonAncestor(BSTNode*& root, BSTNode*& N1, BSTNode*& N2){
	if (root == NULL){ return NULL; }

	BSTNode* lChild = firstCommonAncestor(root->left, N1, N2);
	BSTNode* rChild = firstCommonAncestor(root->right, N1, N2);

	if (lChild != NULL && rChild != NULL){
		return root;
	}

	if (root == N1){ return N1; }
	if (root == N2){ return N2; }

	if(lChild != NULL && rChild == NULL){
		return lChild;
	}else{
		return rChild;
	}
	return NULL;
}

int main(){
	BSTree tree;
	BSTNode* root = tree.Root();
	tree.Insert(root, 5);
	tree.Insert(root, 3);
	tree.Insert(root, 8);
	tree.Insert(root, 2);
	tree.Insert(root, 4);
	tree.Insert(root, 7);
	tree.Insert(root, 10);
	tree.Insert(root, 1);
	tree.Insert(root, 6);
	tree.Insert(root, 9);

	tree.print(root, 0);

	BSTNode* N1 = tree.target(root, 6);
	BSTNode* N2 = tree.target(root, 8);


	BSTNode* commonAncestor = tree.firstCommonAncestor(root, N1, N2);

	cout << commonAncestor->data << endl;
}


