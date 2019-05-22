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



Node* LinkedList::sumList(Node* n1, Node* n2){
    int sum = 0;
    int firstDigit = 0;
    int tenthDigit = 0;
    vector<int> digits(2, 0);
    Node* n1head = n1;
    Node* n2head = n2;

    if((n1 != NULL) && (n2 == NULL)){ return n1; }
    else if((n1 == NULL) && (n2 != NULL)){ return n2; }
    else if((n1 == NULL) && (n2 == NULL)){ return NULL; }
    
    else{
        while(n1 != NULL){
            sum = n1->data + n2->data + tenthDigit;
            if(sum >= 10){
                digits = getDigits(sum);
                tenthDigit = digits[0];
                firstDigit = digits[1];
            }else{
                tenthDigit = 0;
                firstDigit = sum;
            }
            if((n1->next == NULL) && (n2->next != NULL)){
                Node *zeroNode = new Node();
                zeroNode->data = 0;
                n1->next = zeroNode;
            }else if((n1->next == NULL) && (n2->next == NULL)){
                if(tenthDigit == 1){
                    Node *lastDigit = new Node();
                    lastDigit->data = tenthDigit;
                    n1->next = lastDigit;
                    return n1head;
                }
            }else if((n1->next != NULL) && (n2->next == NULL)){
                Node *zeroNode = new Node();
                zeroNode->data = 0;
                n2->next = zeroNode;
            }
            n1->data =  firstDigit;

            n1 = n1->next;
            n2 = n2->next;
        }
    }
    return n1head;
}



vector<int> LinkedList::getDigits(int num_){
    vector<int> ret;
    string iStr = to_string(num_);

    for (int i = iStr.size() - 1; i >= 0; --i)
    {
        int units = pow(10, i);
        int digit = num_ / units % 10;
        ret.push_back(digit);
    }   

    return ret;
}




int main (){
    cout << endl;

    LinkedList list1;
    list1.append(5);
    list1.append(6);
    list1.append(3);
    list1.printList();
    Node* head = list1.returnHead();

    LinkedList list2;
    list2.append(8);
    list2.append(4);
    list2.append(2);
    list2.printList();
    Node* head2 = list2.returnHead();

    cout << "+\n_____________________________\n" << endl;

    Node* summation = list1.sumList(head, head2);

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
    cout << "Rememeber the Summation is reversed! \n" << endl;
}






