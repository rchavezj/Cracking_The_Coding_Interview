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

//O(n) time complexity
//O(1) memory space. 
bool LinkedList::palindrome(){
    int count = 0;
    LinkedList *list = this;
    Node *fastPtr = list->head;
    Node *slowPtr = list->head;

    while(fastPtr != NULL) {
        if (fastPtr->next == NULL){ break; }
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
        count++;
    }

    Node *nextNode = NULL;
    Node *previousNode = NULL;
    Node *cursor = slowPtr;
    while(cursor != NULL) {
        nextNode = cursor->next;
        cursor->next = previousNode;
        previousNode = cursor;
        cursor = nextNode;
    }

    int testCounter = 1;
    Node *cursor1 = list->head;
    Node *cursor2 = previousNode;
    while(cursor1 != NULL) {
        if((count == testCounter) && 
            (cursor1->data == cursor2->data)){
            reverse(previousNode);
            return true;
        }else if(cursor2 == cursor1){
            reverse(previousNode);
            return true;
        }else if(cursor1->data != cursor2->data){
            return false;
        }
        cursor1 = cursor1->next;
        cursor2 = cursor2->next;
        testCounter++;
    }

    return false;
}


void LinkedList::reverse(Node *head){
    Node *nextNode = NULL;
    Node *previousNode = NULL;
    Node *cursor = head;
    while(cursor != NULL) {
        nextNode = cursor->next;
        cursor->next = previousNode;
        previousNode = cursor;
        cursor = nextNode;
    }
    head = previousNode;
}



int main (){
    LinkedList list;

    list.append(1);
    list.append(2);
    list.append(4);
    list.append(4);
    list.append(2);
    list.append(1);

    list.printList();

    bool palindromeTest = list.palindrome();

    if(palindromeTest){
        cout << "The list is a palindrome! " << endl;
    }else{
        cout << "The list is NOT a palindrome! " << endl;
    }
    cout << endl;

    list.printList();

    bool palindromeTest2 = list.palindrome();

    if(palindromeTest2){
        cout << "The list is a palindrome! " << endl;
    }else{
        cout << "The list is NOT a palindrome! " << endl;
    }
    cout << endl;

    list.printList();
}




