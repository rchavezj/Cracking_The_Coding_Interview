#include <tuple>
#include "../chapter4/BSTree.h"
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



int BSTree::noInitialParent(BSTNode*& child){
	static BSTNode* parent = NULL;
	return longestConsecutive(parent, child, 0);
}

int BSTree::longestConsecutive(BSTNode*& parent, BSTNode*& child, int count){
	if (child == NULL){ return count; }
	
	if (parent != NULL && parent->data == child->data - 1){
		count++;
	}
	
	else{
		count = 1;
	}

	int lChildPath = longestConsecutive(child, child->left, count);
	int rChildPath = longestConsecutive(child, child->right, count);

	return max(count, max(rChildPath, lChildPath));
}



int main(){

	BSTree tree;
	BSTNode* root = tree.Root();
	
	tree.Insert(root, 1);
	tree.Insert(root, 3);
	tree.Insert(root, 2);
	tree.Insert(root, 4);
	tree.Insert(root, 5);
	tree.Insert(root, 7);
	tree.Insert(root, 8);
	tree.Insert(root, 9);
	tree.Insert(root, 10);

	tree.print(root, 0);

	cout << endl;

	cout << tree.noInitialParent(root) << endl;
}






