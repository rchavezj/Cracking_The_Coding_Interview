#include <tuple>
#include "list.h"
#include <iostream>
#include <map>

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
    cout << "Length of the List -> (";
    cout << length << ")" << endl;
    cout << "List of Elements ---> (";
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
    cout << ")\n"<< endl;
}

//O(n^2) single linked list
void LinkedList::followUpRemoveDubs(){ 
    if(length > 1){
        LinkedList *list = this;
        Node *cursor1 = list->head;
        while(cursor1 != NULL){
            Node *cursor2 = cursor1;
            while(cursor2->next != NULL){
                if(cursor2->next->data == cursor1->data){
                    delete(cursor2->next);
                    cursor2->next = cursor2->next->next;
                    length--;
                }else{
                    cursor2 = cursor2->next;
                }
            }
            cursor1 = cursor1->next;
        }
    }
}

//O(n^2) double linked list
void LinkedList::followUpRemoveDubs2ndTry(){
    LinkedList *list = this;
    Node *cursor1 = list->head;
    while(cursor1 != NULL) {
        Node *cursor2 = cursor1->next;
        while(cursor2 != NULL) {
            if(cursor2->data == cursor1->data){
                cursor2->prev->next = cursor2->next;
                if(cursor2->next != NULL){
                    cursor2->next->prev = cursor2->prev;
                }
                delete(cursor2);
                length--;
            }
            cursor2 = cursor2->next;
        }
        cursor1 = cursor1->next;
    }
}





int main (){

    LinkedList list;

    list.append(2);
    list.append(3);
    list.append(2);
    list.append(3);
    list.append(2);

    list.printList();

    list.followUpRemoveDubs();

    list.printList();

    return 0;
}





