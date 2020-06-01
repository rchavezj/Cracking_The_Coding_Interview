#include "list.h"
#include <vector>
#include <iostream>
#include <math.h> 



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
    if(cursor == NULL){
        cout << "Empty";
    }else{
        cout << "\t";
        while(cursor != NULL){
            if(cursor->next == NULL){
                cout << cursor->data; 
            }else{
                cout << cursor->data << " -> ";
            }
            cursor = cursor->next;
        }
        cout << endl;
    }
}



Node* LinkedList::followUpSumList(Node* n1, Node* n2){
    return n1;
}



vector<int> LinkedList::getDigits(int num_){
    vector<int> ret;
    string iStr = to_string(num_);

    for (int i = iStr.size() - 1; i >= 0; --i){
        int units = pow(10, i);
        int digit = num_ / units % 10;
        ret.push_back(digit);
    }   

    return ret;
}




int main (){
    cout << endl;

    LinkedList list1;
    list1.append(9);
    list1.append(7);
    list1.append(4);
    list1.printList();
    Node* head = list1.returnHead();

    LinkedList list2;
    list2.append(2);
    list2.append(3);
    list2.append(5);
    list2.printList();
    Node* head2 = list2.returnHead();

    cout << "+\n_____________________________\n" << endl;

    Node* summation = list1.followUpSumList(head, head2);

    cout << "\t";
    while(summation != NULL){
        if(summation->next != NULL){
            cout << summation->data << " -> ";
        }else{
            cout << summation->data;
        }
        summation = summation->next;
    }
    cout << "\n" << endl;
}






