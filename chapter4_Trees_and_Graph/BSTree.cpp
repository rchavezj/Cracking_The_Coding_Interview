#include <tuple>		// std::tuple
#include <vector>		// std::vector
#include <queue>        // std::queue
#include <iomanip>		// std::setw
#include <algorithm>    // std::max
#include <iostream>		// std::cout
#include "BSTree.h"
#include <string>

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

int BSTree::treeLength(){
	return length;
}


void BSTree::Insert(BSTNode*& cursor, int item){
   if(cursor == NULL){
    	BSTNode *newNode = new BSTNode();
    	newNode->data = item;
    	cursor = newNode;
    	length++;
    }else{
		if (item <= cursor->data){
			Insert(cursor->left, item);
		}else{
			Insert(cursor->right, item);
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



void BSTree::ListofDepths(BSTNode*& cursor){
	if(cursor == NULL){
		cout << "Empty List";
		return;
	}
	int i = 0;
	queue<BSTNode*> queueBST;
	queueBST.push(cursor);
	queueBST.push(NULL);
	LinkedList temp;
	vectorList.push_back(temp);
	while(!queueBST.empty()){
		cursor = queueBST.front();
		queueBST.pop();
		if(cursor != NULL){
			vectorList[i].append(cursor->data);
			if(cursor->left != NULL){
				queueBST.push(cursor->left);
			}
			if(cursor->right != NULL){
				queueBST.push(cursor->right);
			}
		}else{
			vectorList[i].printList();
			if(!queueBST.empty()){
				vectorList.push_back(temp);
				i++; queueBST.push(NULL);
			}
		}
	}
} 


void BSTree::ListofDepthsStrings(BSTNode*& root){
	if(root == NULL){
		cout << "Empty List";
		return;
	}
	int i = 1;
	queue<BSTNode*> queueBST;
	queueBST.push(root);
	queueBST.push(NULL);
	cout << "Level ";
	cout << i << ": ";
	while(!queueBST.empty()){
		root = queueBST.front();
		queueBST.pop();
		if(root != NULL){
			cout << root->data;
			cout << " ";
			if(root->left != NULL){
				queueBST.push(root->left);
			}
			if(root->right != NULL){
				queueBST.push(root->right);
			}
		}else{
			if(!queueBST.empty()){
				cout << endl;
				cout << "Level ";
				i++; cout << i << ": ";
				queueBST.push(NULL);
			}
		}
	}
}



void BSTree::ListofDepthsRecursively(BSTNode*& root, int depth){
	if (root == NULL) return; 
	LinkedList temp;
	vectorListRecursive.push_back(temp);
	ListofDepthsRecursively(root->left, depth+1);
	vectorListRecursive[depth].append(root->data);
	ListofDepthsRecursively(root->right, depth+1);
}
void BSTree::ListofDepthsRecursivelyPrint(vector<LinkedList> vectorListRecursive){
	for (int i = 0; i < vectorListRecursive.size()-1; ++i){
		cout << "Level " << i+1 << " LinkedList: ";
		vectorListRecursive[i].printList();
	}
}



bool BSTree::checkBalanced(BSTNode*& root){
	if(root == NULL){return true;}
	int leftHeight = height(root->left);
	int rightHeight = height(root->right);

	bool checkLeft = checkBalanced(root->left);
	bool checkRight = checkBalanced(root->right);

	if(abs(leftHeight-rightHeight) <= 1
		&& checkLeft
		&& checkRight){ return true; }
	return false;
}
int BSTree::height(BSTNode*& root){
	if(root == NULL){return 0;}
	int leftHeight = height(root->left);
	int rightHeight = height(root->right);
	return 1 + max (leftHeight, rightHeight);
}




bool BSTree::validateBST(BSTNode*& root, int min, int max){
	if(root == NULL){ return true; }
	
	if(root->data > max && root->data <= min){return false;}

	bool leftSubtree = validateBST(root, min, root->data);
	bool rightSubtree = validateBST(root, root->data + 1, max);

	return leftSubtree && rightSubtree;
}

BSTNode* BSTree::successorInOrder(BSTNode*& root){
	if(root == NULL){ return NULL; }
	static BSTNode* successor;
	if(root->left==NULL){
		successor = root;
	}else{
		successor = successorInOrder(root->left);
	}
	return successor;
}

BSTNode* BSTree::successorInOrder(BSTNode*& root, int target){
	if(root == NULL){ return NULL; }
	static int flag = 0;
	static BSTNode* successor = NULL;
	if(root->data == target){
		if(root->right != NULL){
			successor = successorInOrder(root->right);
			return successor;
		}
		else{
			flag = 1;
			return successor;
		}
	}else{
		successorInOrder(root->left, target);
		if(flag == 1){
			flag = 0;
			successor = root; 
			return successor;
		}
		successorInOrder(root->right, target);
	}return successor;
}


BSTNode* BSTree::successorPreOrder(BSTNode*& root, int target){
	if(root == NULL){ return NULL; }
	static int flag = 0;
	static BSTNode* successor = NULL;
	if(root->data == target){
		if(root->left != NULL){
			successor = root->left;
			return successor;
		}else{
			if(root->right != NULL){
				successor = root->right;
				return successor;
			}else{
				flag = 1;
				return successor;
			}
		}
	}else{
		if(flag == 1){
			flag = 0;
			successor = root; 
			return successor;
		}
		successorPreOrder(root->left, target);
		successorPreOrder(root->right, target);
	}return successor;
}


BSTNode* BSTree::successorPostOrder(BSTNode*& root){
	if(root == NULL){ return NULL; }
	static BSTNode* successor;
	if(root->left==NULL){
		if(root->right == NULL){
			successor = root;
		}else{
			successor = successorPostOrder(root->right);
		}
	}else{
		successor = successorPostOrder(root->left);
	}
	return successor;
}
BSTNode* BSTree::successorPostOrder(BSTNode*& root, int target){
	if(root == NULL){ return NULL; }
	static int flag = 0;
	static BSTNode* successor = NULL;
	if(root->data == target){
		if(root->right != NULL){
			successor = successorPostOrder(root->right);
			return successor;
		}
		else{
			flag = 1;
			return successor;
		}
	}else{
		successorPostOrder(root->left, target);
		successorPostOrder(root->right, target);
		if(flag == 1){
			flag = 0;
			successor = root; 
			return successor;
		}
	}return successor;
}


BSTNode* BSTree::firstCommonAncestor(BSTNode*& root, int root1, int root2){
	if(root == NULL){ return NULL; }

	if(root->data == root1 
		|| root->data == root2){
	    return root;
	}
	BSTNode* left = firstCommonAncestor(root->left, root1, root2);
	BSTNode* right = firstCommonAncestor(root->right, root1, root2);

	if(left != NULL && right != NULL){
	    return root;
	}
	return (left != NULL) ? left : right;
}



vector<int> BSTree::findBloodLine(BSTNode*& root, int missingChild){
	if(root == NULL){return vector<int>();}
	if(root->data == missingChild){
		cout << "Missing child found: " << root->data << endl;
		vector<int> bloodLine;
		bloodLine.insert(bloodLine.begin(), root->data);
		return bloodLine;
	}
	vector<int> leftChild = findBloodLine(root->left, missingChild);
	vector<int> rightChild = findBloodLine(root->right, missingChild);

	if(!leftChild.empty()){
		leftChild.insert(leftChild.begin(), root->data);
	}else{
		if(!rightChild.empty()){
			rightChild.insert(rightChild.begin(), root->data);
		}
	} 
	return (!leftChild.empty()) ? leftChild : rightChild;
}

BSTNode* BSTree::firstCommonAncestor(vector<int>childOneBloodLine, vector<int> childTwoBloodLine){
	auto maxLength = min(childOneBloodLine.size(), childTwoBloodLine.size());
 
	for(int i = 1; i < maxLength; i++){
		if(childOneBloodLine[i] != childTwoBloodLine[i]){
			BSTNode* commonAncestor;
			commonAncestor->data = childOneBloodLine[i-1];
			return commonAncestor;
		}
	}return NULL;
}



void BSTree::BSTSequences(BSTNode*& root){}


bool checkSubtree(string inT1, string inT2, string postT1, string postT2){
	cout << "inT1: " << inT1 << endl;
	cout << "inT2: " << inT2 << endl;
	cout << "postT1: " << postT1 << endl;
	cout << "postT2: " << postT2 << endl;
	bool exists1 = inT1.find(inT2) != string::npos;
	bool exists2 = postT1.find(postT2) != string::npos;
	return exists1 && exists2;
}string BSTree::printInOrder(BSTNode*& root, string T){
	if (root == NULL){return T;}
	string left = printInOrder(root->left, T);
	string right = printInOrder(root->right, T);
	return left + to_string(root->data) + " " + right;
}string BSTree::printPostOrder(BSTNode*& root, string T){
	if (root == NULL){return T;}
	string left = printPostOrder(root->left, T);
	string right = printPostOrder(root->right, T);
	return left + right + to_string(root->data) + " ";
}

BSTNode* BSTree::randomNode(BSTNode*& root){return NULL;}




tuple<bool, vector<string>, int> BSTree::pathsWithSum(BSTNode*& root, int sum){
	if(root == NULL) return make_tuple(false, summationList, 0);
	if(root->data == sum){
		string temp;
		summationList.push_back(temp);
		summationList[summationList.size()-1].insert(0, to_string(root->data) + " ");
		return make_tuple(true, summationList, 1);
	}else{
		tuple<bool, vector<string>, int> leftPath = pathsWithSum(root->left, sum - root->data);
		tuple<bool, vector<string>, int> rightPath = pathsWithSum(root->right, sum - root->data);
	
	 	int combineCounters = get<2>(leftPath) + get<2>(rightPath);

		if( get<0>(leftPath) ){
			if( get<0>(rightPath) ){
				for(int i = 0; i < combineCounters; i++){
					summationList[i].insert(0, to_string(root->data)  + " ");
				}
			}else{
				for(int i = 0; i < get<2>(leftPath); i++){
					summationList[i].insert(0, to_string(root->data) + " ");
				}
			}
		}else{
			if(get<0>(rightPath)){
				for(int i = 0; i < get<2>(rightPath); i++){
					summationList[i].insert(0, to_string(root->data) + " ");
				}
			}
		}return make_tuple(true ,summationList, combineCounters);
	}
}


int BSTree::maximumPath(BSTNode*& root, int sum){
	if(root==NULL){return 0;}
	if(root->data == sum){return 1;}

	int leftLength = maximumPath(root->left, sum-root->data);
	int rightLength = maximumPath(root->right, sum-root->data);

	if(leftLength != 0){
		if(rightLength != 0){
			// if both childs return an existing path
			// return the max path
			return max(leftLength, rightLength) + 1;
		}else{
			//if we only have a left path summation
			return leftLength + 1;
		}
	}else{
		return rightLength + 1;
	}
	return 0;
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


int main(){
	cout << endl;
	cout << endl;
	//////////////////////////////////////////
	//////////// Insert function /////////////
	BSTree tree;
	BSTNode* tempRoot = tree.Root();
	cout << "tree(1)\n"<<endl;
	cout << "Insert function" << endl;
	tree.Insert(tempRoot, 40);
	tree.Insert(tempRoot, 30);
	tree.Insert(tempRoot, 35);
	tree.Insert(tempRoot, 50);
	tree.Insert(tempRoot, 20);
	tree.Insert(tempRoot, 45);
	tree.Insert(tempRoot, 50);
	tree.print(tempRoot, 0);
	//////////////////////////////////////////
	//////////////////////////////////////////

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	//////////////////////////////////////////
	///////// Minimal Tree function //////////
	BSTree tree2;
	BSTNode* tempRoot2 = tree2.Root();
	vector<int> v;
	cout << "tree(2)"<<endl;
	cout << "Minimal Tree function" << endl;
	v.push_back(100);
	v.push_back(200);
	v.push_back(300);
	v.push_back(400);
	v.push_back(500);
	v.push_back(600);
	v.push_back(700);
	tree2.MinimalTree(tempRoot2, v, 0, v.size());
	tree2.print(tempRoot2, 0);
	//////////////////////////////////////////
	//////////////////////////////////////////

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	//////////////////////////////////////////
	//////////// List of Depths //////////////
	BSTree tree3;
	cout << "tree(3)"<<endl;
	cout << "List of Depths" << endl;
	BSTNode* tempRoot3 = tree3.Root();
	tree3.Insert(tempRoot3, 4444);
	tree3.Insert(tempRoot3, 3333);
	tree3.Insert(tempRoot3, 5555);
	tree3.Insert(tempRoot3, 6666);
	tree3.Insert(tempRoot3, 3334);
	tree3.Insert(tempRoot3, 5534);
	tree3.Insert(tempRoot3, 2222);
	tree3.print(tempRoot3, 0);
	cout << endl;
	cout << "tree to LinkedList" << endl;
	tree3.ListofDepths(tempRoot3);
	//////////////////////////////////////////
	//////////////////////////////////////////

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	//////////////////////////////////////////
	//////// List of Depths Strings //////////
	cout << "tree(1)" << endl;
	cout << "List of Depths Strings" << endl;
	tree.ListofDepthsStrings(tempRoot);
	cout << endl;
	cout << endl;
	cout << "tree(2)" << endl;
	cout << "List of Depths Strings" << endl;
	tree2.ListofDepthsStrings(tempRoot2);
	cout << endl;
	cout << endl;
	//////////////////////////////////////////
	//////////////////////////////////////////
	
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	//////////////////////////////////////////
	/////// List of Depths recursion /////////
	BSTree tree4;
	cout << "tree(4)" << endl;
	cout << "List of Depths recursion" << endl;
	BSTNode* tempRoot4 = tree4.Root();
	tree4.Insert(tempRoot4, 707070);
	tree4.Insert(tempRoot4, 505050);
	tree4.Insert(tempRoot4, 404040);
	tree4.Insert(tempRoot4, 505050);
	tree4.Insert(tempRoot4, 303030);
	tree4.Insert(tempRoot4, 101010);
	tree4.Insert(tempRoot4, 202020);
	tree4.print(tempRoot4, 0);
	tree4.ListofDepthsRecursively(tempRoot4, 0);
	tree4.ListofDepthsRecursivelyPrint(tree4.VectorListRecursive());
	//////////////////////////////////////////
	//////////////////////////////////////////

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	//////////////////////////////////////////
	///////// Balance Tree (Height) //////////
	BSTree tree5;
	cout << "tree(5)" << endl;
	cout << "Balance Tree (Height)" << endl;
	BSTNode* tempRoot5 = tree5.Root();
	tree5.Insert(tempRoot5, 40);
	tree5.Insert(tempRoot5, 50);
	tree5.Insert(tempRoot5, 30);
	tree5.Insert(tempRoot5, 35);
	tree5.Insert(tempRoot5, 20);
	tree5.print(tempRoot5, 0);
	bool Balance = tree5.checkBalanced(tempRoot5);
	cout << Balance << endl;
	if (Balance){
		cout << "The tree is balance"<< endl;
	}else{
		cout << "The tree is NOT balance" << endl;
	}
	//////////////////////////////////////////
	//////////////////////////////////////////

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	//////////////////////////////////////////
	///////////// validateBST  ///////////////
	// Reference if an integer can be NULL  //
	BSTree tree6;
	BSTNode* tempRoot6 = tree6.Root();
	cout << "tree(6)" << endl;
	cout << "validateBST" << endl;
	tree6.Insert(tempRoot6, 4444);
	tree6.Insert(tempRoot6, 3333);
	tree6.Insert(tempRoot6, 5555);
	tree6.Insert(tempRoot6, 6666);
	tree6.Insert(tempRoot6, 3334);
	tree6.Insert(tempRoot6, 5534);
	tree6.Insert(tempRoot6, 2222);
	tree6.print(tempRoot6, 0);
	cout << endl;
	tree6.ListofDepthsStrings(tempRoot6);
	cout << endl;
	bool validate = tree6.validateBST(tempRoot6, -1000, 1000);
	if (validate){
		cout << "This Binary tree is a Binary Search Tree"<< endl;
	}else{
		cout << "This Binary tree is NOT a Binary Search Tree" << endl;
	}
	//////////////////////////////////////////
	//////////////////////////////////////////

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	//////////////////////////////////////////
	/////////// successorPreOrder  ///////////
	/////////// successorInOrder  ////////////
	////////// successorPostOrder  ///////////
	BSTree tree7;
	BSTNode* tempRoot7 = tree7.Root();
	BSTNode* successorInOrder;
	BSTNode* successorPreOrder;
	BSTNode* successorPostOrder;
	cout << "tree(7)" << endl;
	cout << "successorPreOrder" << endl;
	cout << "successorInOrder" << endl;
	cout << "successorPostOrder" << endl;
	tree7.Insert(tempRoot7, 15);
	tree7.Insert(tempRoot7, 10);
	tree7.Insert(tempRoot7, 5);
	tree7.Insert(tempRoot7, 7);
	tree7.Insert(tempRoot7, 1);
	tree7.Insert(tempRoot7, 8);
	tree7.Insert(tempRoot7, 20);
	tree7.Insert(tempRoot7, 17);
	tree7.Insert(tempRoot7, 25);
	tree7.print(tempRoot7, 0);
	int target = 25;
	successorInOrder = tree7.successorInOrder(tempRoot7, target);
	successorPreOrder = tree7.successorPreOrder(tempRoot7, target);
	successorPostOrder = tree7.successorPostOrder(tempRoot7, target);
	cout << endl;
	cout << "Target: " << target << endl;
	if(successorInOrder == NULL){
		cout << "successorInOrder: (NULL)" << endl;
	}else{
		cout << "successorInOrder: " << successorInOrder->data << endl;
	}
	if(successorPreOrder == NULL){
		cout << "successorPreOrder: (NULL)" << endl;
	}else{
		cout << "successorPreOrder: " << successorPreOrder->data << endl;
	}
	if(successorPostOrder == NULL){
		cout << "successorPostOrder: (NULL)" << endl;
	}else{
		cout << "successorPostOrder: " << successorPostOrder->data << endl;
	}
	//////////////////////////////////////////
	//////////////////////////////////////////

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;


	//////////////////////////////////////////
	///////// firstCommonAncestor  ///////////
	BSTree tree8;
	BSTNode* tempRoot8 = tree8.Root();
	cout << "tree(8)" << endl;
	cout << "firstCommonAncestor" << endl;
	tree8.Insert(tempRoot8, 4444);
	tree8.Insert(tempRoot8, 3333);
	tree8.Insert(tempRoot8, 5555);
	tree8.Insert(tempRoot8, 6666);
	tree8.Insert(tempRoot8, 3334);
	tree8.Insert(tempRoot8, 5534);
	tree8.Insert(tempRoot8, 2222);
	tree8.print(tempRoot8, 0);
	cout << endl;
	BSTNode* firstCommonAncestor = tree8.firstCommonAncestor(tempRoot8, 3333, 3334);
	cout << "firstCommonAncestor: " << firstCommonAncestor->data << endl;
	//////////////////////////////////////////
	//////////////////////////////////////////

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	//////////////////////////////////////////
	//// firstCommonAncestor (extra space) ///
	BSTree tree9;
	BSTNode* tempRoot9 = tree9.Root();
	cout << "tree(9)" << endl;
	cout << "firstCommonAncestor (extra space)" << endl;
	tree9.Insert(tempRoot9, 15);
	tree9.Insert(tempRoot9, 10);
	tree9.Insert(tempRoot9, 5);
	tree9.Insert(tempRoot9, 7);
	tree9.Insert(tempRoot9, 1);
	tree9.Insert(tempRoot9, 8);
	tree9.Insert(tempRoot9, 20);
	tree9.Insert(tempRoot9, 17);
	tree9.Insert(tempRoot9, 25);
	tree9.print(tempRoot9, 0);
	cout << endl;
	vector<int>childOneBloodLine = tree9.findBloodLine(tempRoot9, 8);
	cout << "childOneBloodLine: " << endl;
	for (int i = 0; i < childOneBloodLine.size(); i++){
		cout << childOneBloodLine[i] << " ";
	}
	cout << endl;
	cout << endl;
	vector<int>childTwoBloodLine = tree9.findBloodLine(tempRoot9, 1);
	cout << "childTwoBloodLine: " << endl;
	for (int i = 0; i < childTwoBloodLine.size(); i++){
		cout << childTwoBloodLine[i] << " ";
	}
	cout << endl;
	cout << endl;
	BSTNode* yolo = tree9.firstCommonAncestor(childOneBloodLine, childTwoBloodLine);
	cout << "firstCommonAncestor: " << yolo->data << endl;
	//////////////////////////////////////////
	//////////////////////////////////////////

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	//////////////////////////////////////////
	///////////// checkSubtree  //////////////
	BSTree tree10;
	BSTNode* tempRoot10 = tree10.Root();
	cout << "tree(10)" << endl;
	cout << "checkSubtree" << endl;
	tree10.Insert(tempRoot10, 4444);
	tree10.Insert(tempRoot10, 3333);
	tree10.Insert(tempRoot10, 5555);
	tree10.Insert(tempRoot10, 6666);
	tree10.Insert(tempRoot10, 3334);
	tree10.Insert(tempRoot10, 5534);
	tree10.Insert(tempRoot10, 2222);
	tree10.print(tempRoot10, 0);
	cout << endl;
	BSTree tree11;
	BSTNode* tempRoot11 = tree11.Root();
	cout << "tree(11)" << endl;
	tree11.Insert(tempRoot11, 5555);
	tree11.Insert(tempRoot11, 5534);
	tree11.Insert(tempRoot11, 6666);
	tree11.print(tempRoot11, 0);
	cout << endl;
	string temp = "";
	string inT1 = tree10.printInOrder(tempRoot10, temp);
	string inT2 = tree11.printInOrder(tempRoot11, temp);

	string postT1 = tree10.printPostOrder(tempRoot10, temp);
	string postT2 = tree11.printPostOrder(tempRoot11, temp);

	bool checkSubtreeStatus = checkSubtree(inT1, inT2, postT1, postT2);
	cout << endl;
	if (checkSubtreeStatus){
		cout << "tree(11) is a subtree of tree(10)" << endl;
	}else{
		cout << "tree(11) is NOT a subtree of tree(10)" << endl;
	}
	//////////////////////////////////////////
	//////////////////////////////////////////

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	//////////////////////////////////////////
	///////////// pathsWithSum  //////////////
	BSTree tree12;
	BSTNode* tempRoot12 = tree12.Root();
	cout << "tree(12)" << endl;
	cout << "pathsWithSum" << endl;
	tree12.Insert(tempRoot12, 50);
	tree12.Insert(tempRoot12, 35);
	tree12.Insert(tempRoot12, 40);
	tree12.Insert(tempRoot12, 20);
	tree12.Insert(tempRoot12, 20);
	tree12.Insert(tempRoot12, 20);
	tree12.Insert(tempRoot12, 75);
	tree12.Insert(tempRoot12, 100);
	tree12.Insert(tempRoot12, 10);
	tree12.Insert(tempRoot12, 10);
	tree12.print(tempRoot12, 0);
	tuple<bool, vector<string>, int> path = tree12.pathsWithSum(tempRoot12, 125);
	int maxPath = tree12.maximumPath(tempRoot12, 125);
	vector<string> awesome = get<1>(path);
	cout << endl;
	cout << endl;
	cout << "Level:     ";
	for(int i = 0; i <= awesome.size(); i++){
		cout << i+1 << "  " ;
	}
	cout << endl;
	cout << "          ";
	for(int i = 0; i <= awesome.size(); i++){
		cout << " ↓ " ;
	}
	cout << endl;
	for(int i = 0; i < awesome.size(); i++){
		cout << "Path (" << i+1 << "): " << awesome[i] << endl;
	}
	cout << endl;
	cout << "Logest Path in the tree for the summation (125): "<< maxPath << endl;
	cout << "Number of paths that sum up to a given value (125): "<< get<2>(path) << endl;
	//////////////////////////////////////////
	//////////////////////////////////////////

	cout << endl;
	cout << endl;
	return 0;
}





