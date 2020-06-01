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

// Single/Double Linked List
void LinkedList::deleteNode(Node* cursor){
    if( cursor != NULL ){
        if(cursor->next != NULL){
            cursor->data = cursor->next->data;
            delete(cursor->next);
            cursor->next = cursor->next->next;
            length--;
        }else{
            // If the interview ask for a double
            // Linked List approach to delete last node. 
            cursor->prev->next = cursor->next;
            delete(cursor);
            length--;
        }
    }
}

Node* LinkedList::getNode(int index){
    if(index < 0 ){return NULL;}
    LinkedList* list = this;
    Node *cursor = list->head;
    for(int i = 0; cursor!= NULL; i++){
        if(i == index){
            return cursor;
        }
        cursor = cursor->next;
    }
    return NULL;
}







int main(){
    LinkedList list;

    list.append(2); 
    list.append(54);
    list.append(87);  
    list.printList();

    Node *newNode =  list.getNode(1);

    cout << "Delete Node " << newNode->data << endl;
    cout << endl;

    list.deleteNode(newNode);

    list.printList();
}







