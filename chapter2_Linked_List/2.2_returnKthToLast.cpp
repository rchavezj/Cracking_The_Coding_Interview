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


//O(n) if the length was given
void LinkedList::returnKthToLast(int k){
    LinkedList *list = this;
    Node *cursor = list->head;

    for(int i = 0; i < length; i++){
        if(cursor != NULL){
            if(i == k){
                cout << cursor->data << " ";
            }
        }cursor = cursor->next;
    }cout << endl;
}

void LinkedList::place(int k, int element){
    cout << "Node ";
    cout << element << " is ";
    cout << k << " element(s) away from ";
    cout << "the last Node." << endl;
    cout << endl;
}

void LinkedList::outOfBound(){
    cout << "Kth location is out of ";
    cout << "bound from the list" << endl;
}

//O(n) if the length was NOT given!
void LinkedList::returnKthToLast2ndTry(int k){
    if(k < 0){
        outOfBound(); 
        return;
    }
    int flag = 1;
    LinkedList *list = this;
    Node *cursor1 = list->head;

    for(int i = 0; i <= k; i++){
        if(cursor1 == NULL){
            outOfBound();
            flag = 0;break;   
        }
        cursor1 = cursor1->next;
    }

    if(flag == 1){
        Node *cursor2 = list->head;
        while(cursor1 != NULL){
            cursor1 = cursor1->next;
            cursor2 = cursor2->next;
        }
        place(k, cursor2->data);
    }
}



int main (){
	LinkedList list;

    list.append(2);   // index  0   ,  k = 6
    list.append(54);  //        1   ,  k = 5
    list.append(87);  //        2   ,  k = 4
    list.append(55);  //        3   ,  k = 3
    list.append(94);  //        4   ,  k = 2
    list.append(111); //        5   ,  k = 1
    list.append(425); //        6   ,  k = 0

    list.printList();
    list.returnKthToLast2ndTry(3);
}













