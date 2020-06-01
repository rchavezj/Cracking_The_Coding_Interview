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

BSTNode* BSTree::target(BSTNode*& root, int targetInt){
	if (root == NULL){ return NULL; }
	if(root->data == targetInt){return root;}
	else if(root->data > targetInt){return target(root->left, targetInt);}
	else{return target(root->right, targetInt);}
}


BSTNode* BSTree::leftMostSubNode(BSTNode*& root){
	if(root == NULL){ return NULL; }
	if (root->left != NULL){
		return leftMostSubNode(root->left);
	}else{
		return root;
	}
}

tuple<bool, BSTNode*, bool> BSTree::successorInOrderT(BSTNode*& root, BSTNode*& target){
	static BSTNode* successor = NULL;
	if (root == NULL){ return make_tuple(false, successor, false); }
	if (root == target){
		if (root->right != NULL){
			return make_tuple(true, leftMostSubNode(root->right), false);
		}else{
			return make_tuple(false, successor, true);
		}
	}else{
		tuple<bool, BSTNode*,bool> leftChildSuccessor = successorInOrderT(root->left, target);
		if( get<0>(leftChildSuccessor) ){
			return make_tuple(true, get<1>(leftChildSuccessor), false);
		}
		if( get<2>(leftChildSuccessor)){
			return make_tuple(true, root, false);
		}
		tuple<bool, BSTNode*,bool> rightChildSuccessor = successorInOrderT(root->right, target);
		if( get<0>(rightChildSuccessor)  || get<2>(rightChildSuccessor)){
			return make_tuple(false, get<1>(rightChildSuccessor), true);
		}
	}
	return make_tuple(false, successor, false);
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
	BSTNode* targetNode = tree.target(root, 6);

	tuple<bool, BSTNode*,bool> successor = tree.successorInOrderT(root, targetNode);
	BSTNode* successorData = get<1>(successor);

	cout << "targetNode: " << targetNode->data << endl;
	if(successorData == NULL){
		cout << "successorInOrder: (NULL)" << endl;
	}else{
		cout << "successorInOrder: " << successorData->data << endl;
	}

}





