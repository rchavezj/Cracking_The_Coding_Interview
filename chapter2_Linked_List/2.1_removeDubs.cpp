#include <map>
#include <tuple>
#include "list.h"
#include <iostream>
#include <unordered_set>

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


void LinkedList::deleteFront(){
    if(length == 0){
        cout << "(Permission denied!) " << endl;
        cout << "You cannot delete a node. List is empty \n\n";
    }else{
        LinkedList* list = this;
        if(length == 1){
            list->head = list->tail = NULL;
            delete (list->head);
            delete (list->tail);
            length--;
        }else{
            list->head = list->head->next;
            list->head->prev = NULL; 
            delete (list->head->prev);
            length--;
        }
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

//O(n^2)
void LinkedList::removeDubs(){
    if(length > 1){
        map<int, int> Dups;
        LinkedList *list = this;
        Node *cursor = list->head;
        while(cursor != NULL) {
            Dups[cursor->data]++;
            cursor = cursor->next;
            deleteFront();
        }
        for(auto index : Dups){
            append(index.first);
        }
    }
}

//O(n): Double Linked List
void LinkedList::removeDubs2ndTry(){
    if(length > 1){
        map<int, int> dubs;
        LinkedList *list = this;
        Node *cursor = list->head;
        while(cursor != NULL){
            if(dubs[cursor->data] != 1){
                dubs[cursor->data] += 1;
            }else{
                cursor->prev->next = cursor->next;

                if(cursor->next != NULL){
                    cursor->next->prev = cursor->prev;
                }
                delete(cursor);
                length--;
            }
            cursor = cursor->next;
        }
    }
}

//faviorite
//O(n): Single Linked List
void LinkedList::removeDubs3rdTry(){
    if(length > 1){
        Node *previous = NULL;
        map<int, int> dubs;
        LinkedList *list = this;
        Node *cursor = list->head;
        while(cursor != NULL){
            if(dubs[cursor->data] != 1){
                dubs[cursor->data] += 1;
                previous = cursor;
            }else{
                previous->next = cursor->next;
                delete(cursor);
                length--;
            }
            cursor = cursor->next;
        }
    }
}



//O(n) Double Linked list. 
void LinkedList::removeDubs4thTry(){
    if(length > 1){
        Node *prev = NULL;
        unordered_set<int> dubs;
        LinkedList *list = this;
        Node *cursor = list->head;
        while(cursor != NULL){
            if(dubs.find(cursor->data) != dubs.end()){
                prev->next = cursor->next;
            }else{
                dubs.insert(cursor->data);
                prev = cursor;
                delete(cursor);
                length--;
            }cursor = cursor->next;
        }
    }
}


int main (){

    LinkedList list;

    list.append(2);
    list.append(3);
    list.append(2);
    list.append(3);
    list.append(2);
    list.append(3);
    list.append(2);

    list.printList();
    list.removeDubs3rdTry();
    list.printList();

    return 0;
}







