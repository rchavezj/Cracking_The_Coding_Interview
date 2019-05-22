#include <vector>
#include <iomanip>		// std::setw
#include <iostream>
#include "BSTree.h"

using namespace std;

BSTree::BSTree(){
	length = 0;
	root = NULL;
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

void BSTree::MinimalTree(BSTNode*& cursor, vector<int> arr, int left, int right){
	if(left <= right){
		int middle = (left + right)/2;
		if(cursor == NULL){
			BSTNode *newNode = new BSTNode();
			newNode->data = arr[middle];
			cursor = newNode;
			length++;
			MinimalTree(cursor->left, arr, left, middle-1);
			if(middle+1 <= arr.size()-1){
				MinimalTree(cursor->right, arr, middle+1, right);
			}
		}
	}
}

int main (){
	BSTree tree;
	vector<int> arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(4);
	arr.push_back(5);
	arr.push_back(6);
	arr.push_back(7);
	BSTNode* root = tree.Root();
	tree.MinimalTree(root, arr, 0, arr.size()-1);
	tree.print(root, 0);
}






