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

tuple<bool, vector<string>, int > BSTree::pathsWithSum(BSTNode*& root, int sum){
	if (root == NULL){ return make_tuple(false, summationList, 0); }
	if(sum == root->data){
		string temp;
		temp = to_string(root->data) + " ";
		summationList.push_back(temp);
		return make_tuple(true, summationList, 1);
	}else{
		tuple<bool, vector<string>, int> lChildPath = pathsWithSum(root->left, sum - root->data);
		tuple<bool, vector<string>, int> rChildPath = pathsWithSum(root->right, sum - root->data);

		int combineSummationSize = get<2>(lChildPath) + get<2>(rChildPath);

		if(get<0>(lChildPath)){
			if(get<0>(rChildPath)){
				for (int i = 0; i < combineSummationSize; i++){
					summationList[i].insert(0, to_string(root->data) + " ");
				}
			}else{
				for (int i = 0; i < get<2>(lChildPath); i++){
					summationList[i].insert(0, to_string(root->data) + " ");
				}
			}
		}else{
			if (get<0>(rChildPath)){
				for (int i = 0; i < get<2>(rChildPath); i++){
					summationList[i].insert(0, to_string(root->data) + " ");
				}
			}
		}return make_tuple(true, summationList, combineSummationSize);
	}
}


int main(){
	
	BSTree tree;
	BSTNode* root = tree.Root();
	tree.Insert(root, 50);
	tree.Insert(root, 35);
	tree.Insert(root, 40);
	tree.Insert(root, 20);
	tree.Insert(root, 20);
	tree.Insert(root, 20);
	tree.Insert(root, 75);
	tree.Insert(root, 100);
	tree.Insert(root, 10);
	tree.Insert(root, 10);

	tree.print(root, 0);

	tuple<bool, vector<string>, int > summationList = tree.pathsWithSum(root, 125);

	vector<string> summationListString = get<1>(summationList);

	for (int i = 0; i < summationListString.size(); i++)
	{
		cout << summationListString[i] << endl;
	}
}







