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


void LinkedList::partition(int partition){
    Node *partitionHead = NULL;
    Node* partitionTail = NULL;

    LinkedList *list = this;
    Node *cursor = list->head;
    Node *previous = NULL;

    while(cursor != NULL){
        if(partition > cursor->data){
            if(previous != NULL){
                previous->next = cursor->next;
                if(partitionHead != NULL){
                    partitionTail->next = cursor;
                    partitionTail = partitionTail->next;
                }else{ partitionHead = cursor; partitionTail = partitionHead; }
            }}else{ previous = cursor; }
        cursor = cursor->next;
    }
    partitionTail->next = list->head;
    list->head = partitionHead;
}



int main (){
    LinkedList list;
    //list.append(5);
    list.append(3);
    // list.append(5);
    // list.append(2);
    // list.append(8);
    // list.append(5);
    list.append(10);
    list.append(2);
    list.append(1);
    list.append(4);
    list.append(6);
    list.append(5);
    list.append(1);
    //list.append(5);

    cout << "Old list with values higher than partition" << endl;
    list.printList();

    list.partition(5);

    cout << "New list = Old list with values less than partition in front of the list. " << endl;
    list.printList();

    return 0;
}










