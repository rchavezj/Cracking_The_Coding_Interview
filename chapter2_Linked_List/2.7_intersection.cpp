#include "list.h"
#include <iostream>


using namespace std;


LinkedList::LinkedList(){
    length = 0;
    head = tail = NULL; 
}


int LinkedList::listLength(){
    return length;
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
    cout << "List of Elements ---> (";
    if(cursor == NULL){
        cout << "Empty";
    }else{
        while(cursor != NULL){
            if(cursor->next == NULL){
                cout << cursor->data; 
            }else{
                cout << cursor->data << " ";
            }
            cursor = cursor->next;
        }
    }
    cout << ")\n"<< endl;
}

Node* LinkedList::getMiddleNode(){
    LinkedList *list = this;
    Node* slowPtr = list->head;
    Node* fastPtr = list->head;
    while(fastPtr != NULL) {
        if(fastPtr->next == NULL){
            return slowPtr;
        }
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
    }
    return slowPtr;
}

Node* LinkedList::lastNode(){
    LinkedList *list = this;
    Node *previousNode = NULL;
    Node *cursor = list->head;
    while(cursor != NULL) {
        if(cursor->next == NULL){
            return cursor;
        }
        previousNode = cursor;
        cursor = cursor->next;
    }
    return previousNode;
}


void LinkedList::createIntersection(Node *n1Middle, Node *n2Tail){
    n2Tail->next = n1Middle;
}


Node* LinkedList::intersection(Node *n1head, Node *n2head){
    
    int length1 = 0;
    Node* n1 = n1head;
    while(n1!=NULL){
        length1++;
        if(n1->next == NULL){
            break;
        }
        n1 = n1->next;
    }

    int length2 = 0;
    Node* n2 = n2head;
    while(n2 != NULL){
        length2++;
        if(n2->next == NULL){
            break;
        }
        n2 = n2->next;
    }

    if(n1 != n2){ return NULL; }

    int lengthDifference = 0;
    if(length1 > length2){
        n1 = n1head;
        n2 = n2head;
        lengthDifference = length1 - length2;
    }else{
        n1 = n2head;
        n2 = n1head;
        lengthDifference = length2 - length1;
    }

    while(lengthDifference > 0) {
        n1 = n1->next;
        lengthDifference--;
    }

    while(n1 != n2){
        n1 = n1->next;
        n2 = n2->next;
    }

    return n1;
}


int main (){

    // list 1
    LinkedList list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);
    list1.append(8);
    list1.append(9);
    list1.append(10);
    Node* n1head = list1.returnHead();
    Node* n1Middle = list1.getMiddleNode();

    // list 2
    LinkedList list2;
    list2.append(6);
    list2.append(7);
    cout << "List 2" << endl;
    list2.printList();
    Node* n2head = list2.returnHead();
    Node* n2Tail = list2.lastNode();

    // conect list 1 and 2
    // LinkedList list;
    list1.createIntersection(n1Middle, n2Tail);
    Node* intersect = list1.intersection(n1head, n2head);

    // show content 
    // of the list. 
    cout << "List 1" << endl;
    list1.printList();
    cout << "List 2 after intersecting list 1" << endl;
    list2.printList();
    cout << "The two List intersect at node: " << intersect->data << endl;
    cout << endl;
}




