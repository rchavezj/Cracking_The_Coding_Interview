#include <tuple>
#include <vector>
using namespace std;


// Struct inside the class LinkedList
// This is one node which is not needed by the caller. It is just
// for internal work.
struct Node {
    int data;
    Node *next;
    Node *prev;
};



class LinkedList{

    private:
        int length; // to keep reference how long the list. 
        Node *head; // this is the private member variable. It is just a pointer to the first Node
        Node *tail; // this is the private member variable. It is just a pointer to the last Node

    public:
        Node* returnHead(){return head;}
    	LinkedList();
    	int getElement(int index);
    	void getIndex();
    	tuple<int, int> binarySearchList(int L, int R, int element);
    	int listLength();
    	void preppend(int element);
    	void append(int element);
    	void insert(int element, int index);
    	void deleteNode(int index);
    	void deleteFront();
    	void deleteBack();
    	void printList();
        void replaceData(int index, int newData);
        void quickSort(LinkedList *list, int left, int right);


        // 2.1 Remove Dups:
        // Write code to remove duplicates from an unsorted linked list.
        // FOLLOW UP
        // How would you solve this problem if a temporary buffer is not allowed?
        void removeDubs();         // single linked list. 
        void removeDubs2ndTry();   // favorite algorithm double linked list
        void removeDubs3rdTry();  
        void removeDubs4thTry();
        void followUpRemoveDubs();
        void followUpRemoveDubs2ndTry();

        // 2.2 Return Kth to Last: 
        // Implement an algorithm to nd the kth 
        // to last element of a singly linked list.
        void returnKthToLast(int k);  //if length was given
        // if length wasn't given (iterative)
        void outOfBound();     
        void place(int k, int element);
        void returnKthToLast2ndTry(int k);


        // 2.3 Delete Middle Node: 
        // Implement an algorithm to delete a node in 
        // the middle (i.e., any node but the first and 
        // last node, not necessarily the exact middle) 
        // of a singly linked list, given only access to that node.
        // EXAMPLE
        // Input: the node c from the linked list 
        // a->b->c->d->e->f
        // Output: nothing is returned, but 
        // the new linked list looks like 
        // a->b->d->e- >f
        Node* getNode(int index);
        void deleteNode(Node* cursor);

        // 2.4 Partition: 
        // Write code to partition a linked list around a value x,
        // such that all nodes less than x come before all nodes 
        // greater than or equal to x. If x is contained within the 
        // list, the values of x only need to be after the elements 
        // less than x (see below). The partition element x can  
        // appear anywhere in the "right partition"; it does not 
        // need to appear between the left and right partitions.
        void partition(int partition);

        // 2.5 Sum Lists: 
        // You have two numbers represented by a linked list, where 
        // each node contains a single digit. The digits are stored 
        // in reverse order, such that the 1's digit is at the head  
        // of the list. Write a function that adds the two numbers 
        // and returns the sum as a linked list.
        // EXAMPLE
        // Input:  (7 -> 1 -> 6) + (5 -> 9 -> 2). That is,617 + 295. 
        // Output: (2 -> 1 -> 9). That is, 912.
        Node* sumList(Node* N1, Node* L2);
        vector<int> getDigits(int num_);
        // Follow Up:
        // Suppose the digits are stored in forward
        // order. Repeat the above problem. EXAMPLE
        // Input:  (6 -> 1 -> 7) + (2 -> 9 -> 5). That is, 617 + 295. 
        // Output: (9 -> 1 -> 2).Thatis,912.
        Node* followUpSumList(Node* n1, Node* n2);


        // 2.6 Palindrome 
        // Implement a function to check 
        // if a linked list is a palindrome.
        bool palindrome();
        void reverse(Node *head);


        // 2.7 Intersection: 
        // Given two (singly) linked lists, determine if the two 
        // lists intersect. Return the inter­ secting node. Note 
        // that the intersection is de ned based on reference, not 
        // value.That is, if the kth node of the  rst linked list 
        // is the exact same node (by reference) as the jth node 
        // of the second linked list, then they are intersecting.
        void createIntersection(Node *n1Middle, Node *n2Tail);
        Node* intersection(Node *n1head, Node *n2head);

        // 2.8 Loop Detection: 
        // Given a circular linked list, implement an algorithm that 
        // returns the node at the beginning of the loop.
        // DEFINITION
        // Circular linked list: A (corrupt) linked list in which a 
        // node's next pointer points to an earlier node, so as to make 
        // a loop in the linked list.
        // EXAMPLE
        // Input: A -> B -> C -> D -> E -> C[the same C as earlier]
        // Output: C 
        Node* lastNode();
        Node* getMiddleNode();
        void createLoop(Node* initialLoop, Node* lastNodeToLoop);
        Node* loopDetction();
        Node* findIniitialLoop(Node* turtle, Node* rabbit);
};






