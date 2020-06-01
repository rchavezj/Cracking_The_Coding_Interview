#ifndef BS_TREE
#define BS_TREE

#include <vector>
#include <tuple>

using namespace std;

struct BSTNode{
    int data = 0;
    struct BSTNode *left;
    struct BSTNode *right;
};

struct Node {
	int data = 0;
	Node *next;
	Node *prev;
};


class LinkedList{
    private:
        int length; // to keep reference the length of the list. 
        Node *head; // this is the private member variable. It is just a pointer to the first Node
        Node *tail; // this is the private member variable. It is just a pointer to the last Node

    public:
    	LinkedList();
    	void append(int element);
    	void printList();
};

class BSTree: public LinkedList{
	
	private:
		int length;
		BSTNode *root;
		vector<LinkedList> vectorList;
		vector<LinkedList> vectorListRecursive;

		vector<LinkedList> listOfDepths;

		vector<string> summationList;

	public:
		// Constructor
		BSTree();
		//~BSTree();
		// return the root for other classes
		// that do not have access to private root. 
		BSTNode*& Root() { return root; };
		// Return the vector linked list from the recursive function. 
		vector<LinkedList> VectorListRecursive(){return vectorListRecursive;};
		// Return the number
		// of nodes in the tree. 
		int treeLength();
		// Inserting a binary tree. 
		void Insert(int item);
	 	void Insert(BSTNode*& cursor, int item);
		// print an in order traversal tree
		// void print(int index);
		void print(BSTNode*& root, int index);
		// void printInOrder(BSTNode* root);
		// Given a sorted (increasing order) array 
		// with unique integer elements, write an algo­rithm
		// to create a binary search tree with minimal height.
		void MinimalTree(BSTNode*& root, vector<int> arr, int left, int right);
		// Given a binary tree, design an algorithm 
		// which creates a new line of all the 
		// nodes at each depth (e.g., if you have a 
		// tree with depth D, you'll have D number of strings).
		void ListofDepths(BSTNode*& root);
		void ListofDepthsStrings(BSTNode*& root);
		void ListofDepthsRecursively(BSTNode*& root, int depth);
		void ListofDepthsRecursivelyPrint(vector<LinkedList> vectorListRecursive);
		// Implement a function to check if a binary 
		// tree is balanced. For the purposes of this 
		// question, a balanced tree is defined to be a 
		// tree such that the heights of the two subtrees 
		// of any node never differ by more than one.
		bool checkBalanced(BSTNode*& root);
		int height(BSTNode*& node);
		// Implement a function to check if a
		// binary tree is a binary search tree.
		bool validateBST(BSTNode*& root, int min, int max);
		// Write an algorithm to find the "next" 
		// node (i.e., in-order successor) of a 
		// given node in a binary search tree. You may
		// assume that each node has a link to its parent.
		BSTNode* successorInOrder(BSTNode*& root);
		BSTNode* target(BSTNode*& root, int targetInt);
		BSTNode* leftMostSubNode(BSTNode*& root);
		tuple<bool,BSTNode*,bool> successorInOrderT(BSTNode*& root, BSTNode*&);
		
		BSTNode* successorInOrder(BSTNode*& root, int target);
		BSTNode* successorPreOrder(BSTNode*& root, int target);
		BSTNode* successorPostOrder(BSTNode*& root);
		BSTNode* successorPostOrder(BSTNode*& root, int target);
		// Design an algorithm and write code 
		// to find the first common ancestor of two 
		// nodes in a binary tree. Avoid storing 
		// additional nodes in a data structure. NOTE: 
		// This is not necessarily a binary search tree.
		BSTNode* firstCommonAncestor(BSTNode*& root, BSTNode*& N1, BSTNode*& N2);
		BSTNode* firstCommonAncestor(BSTNode*& root, int root1, int root2);
		vector<int> findBloodLine(BSTNode*& root, int missingChild);
		BSTNode* firstCommonAncestor(vector<int>childOneBloodLine, vector<int> childTwoBloodLine);
		// A binary search tree was created by traversing 
		// through an array from left to right and inserting 
		// each element. Given a binary search tree with 
		// distinct elements, print all possible  
		// arrays that could have led to this tree.
		//
		// Input: 			     20
		//					    /   \
		//					  10     30
		// Output:
		//			{20, 10, 30}
		//			{20, 30, 10}
		void BSTSequences(BSTNode*& root);
		// T1 and T2 are two very large binary trees, 
		// with T1 much bigger than T2. Create an
		// algorithm to determine if T2 is a subtree of 
		// T1. A tree T2 is a subtree of T1 if there 
		// exists a node n in T1 such that the subtree 
		// of n is identical to T2. That is, if you cut off
		// the tree at node n, the two trees would be identical.
		//bool checkSubtree(string inT1, string inT2, string postT1, string postT2);
		string printInOrder(BSTNode*& root, string T);
		string printPostOrder(BSTNode*& root, string T);
		// You are implementing a binary tree class from 
		// scratch which, in addition to insert, find, 
		// and delete, has a method getRandomNode() which 
		// returns a random node from the tree. All nodes 
		// should be equally likely to be chosen. Design and
	 	// implement an algorithm for getRandomNode, and explain
 		// how you would implement the rest of the methods.
		BSTNode* randomNode(BSTNode*& root);
		// You are given a binary tree in which each node 
		// contains an integer value (which might be positive 
		// or negative). Design an algorithm to count the 
		// number of paths that sum to a given value. The path does
		// not "need" to start or end at the root or a leaf, but it must
		// go downwards (traveling only from parent nodes to child nodes).
		std::tuple<bool, vector<string>, int > pathsWithSum(BSTNode*& root, int sum);
		// Find the maximum sum path in binary tree
		int maximumPath(BSTNode*& root, int sum);

		int noInitialParent(BSTNode*& child);
		int longestConsecutive(BSTNode*& parent, BSTNode*& child, int count);
		// int search(BSTNode*& root, BSTNode*& parent, int len);
};



#endif





