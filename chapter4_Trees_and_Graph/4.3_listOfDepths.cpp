#include <queue>
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
void LinkedList::printList(){
    LinkedList* list = this;
    Node* cursor = list->head;
    if(cursor == NULL){
        cout << "Empty";
    }else{
        while (cursor != NULL){
            if(cursor->next == NULL){
                cout << cursor->data; 
            }else{
                cout << cursor->data << " ";
            }
            cursor = cursor->next;
        }
    }
    cout << endl;
}
void LinkedList::append(int element){
	Node *newTailNode = new Node();   
    newTailNode->data = element;      
    
    LinkedList* list = this;
    Node* cursor = list->tail;

    if(cursor!= NULL){
        list->tail->next = newTailNode;
        newTailNode->prev = list->tail;
        list->tail = newTailNode;
        length++;
    }else{
        list->tail = list->head = newTailNode;
        length++;
    }
}

void BSTree::Insert(BSTNode*& root, int item){
	BSTNode* newNode = new BSTNode(); 
	newNode->data = item;

	if(root == NULL){
		root = newNode;
		return;
	}
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

void BSTree::ListofDepths(BSTNode*& root){
	if (root == NULL){return;}
	int i = 0;
	queue<BSTNode*> levelTraverse;
	levelTraverse.push(root);
	levelTraverse.push(NULL);
	LinkedList temp;
	listOfDepths.push_back(temp);
	while(!levelTraverse.empty()) {
	    root = levelTraverse.front();
	    levelTraverse.pop();
	    if (root != NULL){
	    	listOfDepths[i].append(root->data);
	    	if (root->left != NULL){
	    		levelTraverse.push(root->left);
	    	}
	    	if (root->right != NULL){
	    		levelTraverse.push(root->right);
	    	}
	    }else{
	    	listOfDepths[i].printList();
	    	if (!levelTraverse.empty()){
	    		listOfDepths.push_back(temp);
	    		i++; levelTraverse.push(NULL);
	    	}
	    }
	}
}


int main(){
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
	cout << endl;
	tree.ListofDepths(root);
}










