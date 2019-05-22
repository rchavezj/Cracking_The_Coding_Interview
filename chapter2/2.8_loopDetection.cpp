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

void LinkedList::createLoop(Node* initialLoop, Node* lastNodeToLoop){
    lastNodeToLoop->next = initialLoop;
}

// Floyd’s Cycle-Finding Algorithm:
Node* LinkedList::loopDetction(){
    LinkedList *list = this;
    Node *rabbit = list->head;
    Node *turtle = list->head;

    while(rabbit != NULL){
        if(rabbit->next == NULL){
            return NULL;
        }

        turtle = turtle->next;
        rabbit = rabbit->next->next;

        if(rabbit == turtle){
            Node* loopNode = findIniitialLoop(list->head, rabbit);
            return loopNode;
        }
    }
    return NULL;
}

// We have a cycle! Now find the
// node that initiallizes the cycle. 
Node* LinkedList::findIniitialLoop(Node* turtle, Node* rabbit){
    while(turtle != rabbit){
        turtle = turtle->next;
        rabbit = rabbit->next;
    }
    return turtle;
}

int main (){
    LinkedList list;

    list.append(1); //a
    list.append(2); //b
    list.append(3); //c
    list.append(4); //d
    list.append(5); //e

    list.printList();

    Node* initialLoop = list.getMiddleNode();

    Node* lastNodeToLoop = list.lastNode();

    list.createLoop(initialLoop, lastNodeToLoop);

    Node* foundLoop = list.loopDetction();

    cout << "The loop starts at: " << foundLoop->data << endl;

    // Try to print the list again, 
    // you will end up with an infinite loop
    list.printList();
}











