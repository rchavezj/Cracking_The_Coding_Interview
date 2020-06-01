#include <tuple>
#include "list.h"
#include <iostream>
#include <map>

using namespace std;


// constructor
LinkedList::LinkedList(){
    length = 0;
    head = tail = NULL; // set head to NULL
}


int LinkedList::listLength(){
    return length;
}

// This prepends a new value at the beginning of the list
void LinkedList::preppend(int element){
    Node *newHeadNode = new Node();     // create new Node
    newHeadNode->data = element;        // set value into the new Node
    
    //created a new list 
    LinkedList* list = this;            

    // Create a temp node from the 
    // declared list to check if the
    // head exist within the list. 
    Node* cursor = list->head;  

    if(cursor!= NULL){
        // (1) First point 
        //     the head to new node.
        list->head->prev = newHeadNode;
        // (2) Have the new  
        //     node point to the head. 
        newHeadNode->next = list->head;
        // (3) Set the new 
        //     node to be the new head.
        list->head =  newHeadNode;
        // (4) Increment the variable length to
        //     reference the length of the list. 
        length++;
    }else{
        // (1) If the list is empty, 
        //     tail and head are equal to the new node 
        list->head = list->tail = newHeadNode;
        // (2) Increment the variable length to
        //     reference the length of the list.
        length++;
    }
}

// This appends a new value at the end of the list
void LinkedList::append(int element){
    Node *newTailNode = new Node();    // create new Node. 
    newTailNode->data = element;       // set value into the new Node
    
    // created a new list
    LinkedList* list = this;
    // create a temp node from the 
    // declared list to check if the
    // tail exist within the list.
    Node* cursor = list->tail;

    if(cursor!= NULL){
        // (1) First point 
        //     the tail to new node. 
        list->tail->next = newTailNode;
        // (2) Have the new 
        //     node point point to tail.
        newTailNode->prev = list->tail;
        // (3) Set the new
        //     node to be new tail. 
        list->tail = newTailNode;
        // (4) Increment the variable length to
        //     reference the length of the list.
        length++;
    }else{
        // (1) If the list is empty, 
        //     tail and head are equal to the new node 
        list->tail = list->head = newTailNode;
        // (2) Increment the variable length to
        //     reference the length of the list.
        length++;
    }
}

int LinkedList::getElement(int index){
    if((length == 0) || (index < 0) || (index >= length)){
        cout << "Cannot grab Element. \nRequested index ("<<index<<") is Out of Bound: ";
    }else{
        LinkedList* list = this;
        Node* cursor = list->head;
        for(int i = 0; i < length; i++){
            if (i == index){
                return cursor->data;
            }
            cursor = cursor->next;
        }  
    }
    return -1;
}


void LinkedList::getIndex(){
    if(length == 0){
        cout << "Out of bound\n"<<endl;
    }else{
        LinkedList* list = this;
        Node* cursor = list->head;
        for(int i = 0; i < length; i++){
                //return i;
                cout << i << " ";
            cursor = cursor->next;
        }cout << "\n";  
    }
}

void LinkedList::replaceData(int index, int newData){
    if(length == 0){
        cout << "Out of bound\n"<<endl;
    }else{
        LinkedList* list = this;
        Node* cursor = list->head;
        for(int i = 0; i < length; i++){
            if(i == index){
                cursor->data = newData;
                break;
            }
            cursor = cursor->next;
        }
    }
}

void LinkedList::quickSort(LinkedList *list, int left, int right){
    int i = left, j = right;
    int tmp;

    int pivot = list->getElement((left + right) / 2);

    /* partition */
    while (i <= j) {
        while (list->getElement(i) < pivot)
              i++;
        while (list->getElement(j) > pivot)
              j--;
        if (i <= j) {
              tmp = list->getElement(i);
              //list->getElement(i) = list->getElement(j);
              replaceData(i, list->getElement(j));
              //list->getElement(j) = tmpnext;
              replaceData(j, tmp);
              i++;
              j--;
        }
    };

    /* recursion */
    if (left < j)
        quickSort(list, left, j);
    if (i < right)
        quickSort(list, i, right);
}

tuple<int, int> LinkedList::binarySearchList(int L, int R, int element){
    LinkedList* list = this;
    quickSort(list, L, R);
    if(L <= R){
       int middle = L + (R - L)/2;
       cout << "element: " << element << ", list->getElement(middle): " << list->getElement(middle) << endl;
        if( list->getElement(middle) == element) {
            return make_tuple(middle, list->getElement(middle));
        }if(element < list->getElement(middle)){
            return binarySearchList(L, middle-1, element);
        }
        return binarySearchList(middle+1, R, element);   
    }
    return make_tuple(-1, -1);
}


void LinkedList::insert(int element, int index){
    // Precondition if the requested index
    // is out of bound from the length of the list. 
    if( (index > length) ||  (index < 0) ){
        cout << "Out of bound insert request for Element (";
        cout << element << ") index ("<< index <<") denied\n" << endl;
    }else{
        // Create a new node from the stuct class
        Node *insertedNode = new Node();
        // Set a value for the new node. 
        insertedNode->data = element;

        // created a new list
        LinkedList* list = this;
        // create a temp node from the 
        // declared list to check if the
        // tail exist within the list.
        Node* cursor = list->head;

        // Only way to insert a new  
        // node on an empty list, the length
        // of the list has to be empty 
        if((cursor == NULL) && (length == 0)){
            // (1) If the list is empty, 
            //     tail and head are equal to the new node 
            list->tail = list->head = insertedNode;
            // (2) Increment the variable length to
            //     reference the length of the list.
            length++;               
        }
        // (1) preppend algorithm
        // (2) This else condition is if we have 
        //     at least one node. and also
        //     want to place our new node in the front of the list. 
        else if( (length != 1) && (index == 0)){
            // (1) First point 
            //     head node to new Node. 
            list->head->prev = insertedNode;
            // (2) Have new node
            //     point back to the head. 
            insertedNode->next = list->head;
            // (3) Set the new 
            //     head to be new Node.  
            list->head =  insertedNode;
            // (4) Increment the variable length to
            //     reference the length of the list.
            length++;
        }
        // Append Algorithm
        // If we insert at the end of the 
        // list and also have at least one node. 
        else if((length != 1) && (index == length)){
            // (1) First point 
            //     the tail node to the new Node. 
            list->tail->next = insertedNode;
            // (2) Next point the 
            //     new Node back to the Tail Node
            insertedNode->prev = list->tail;
            // (3) Have the new Node
            //     be set as new tail. 
            list->tail = insertedNode;
            // (4) Increment the variable length to
            //     reference the length of the list.
            length++;
        }else{
            // This loop is used to insert any other 
            // node that is not the front or the back
            // of the list since the algorithm is already  
            // implemented in the beginning of this function. 
            for (int i = 0; i < length; ++i){
                if((i == index) && (length > 1)){
                    // Once our iterate varaible finds 
                    // the location of the requested index, 
                    // the new Node will be placed inside the list 
                    // into the index location we requested. The old
                    // Node that was placed on the requested index location will be
                    // shifted to the right (index + 1) to make room for the new Node. 

                    // (1) First point the previous Node
                    //     the cursor was looking to new Node. 
                    cursor->prev->next = insertedNode;
                    // (2) Next point the New node to the
                    //     previous Node the cursor was looking. 
                    insertedNode->prev = cursor->prev;
                    // (3) Have the current cursor
                    //     Node, and every node after the 
                    //     Cursor Node in the list, shift to the right
                    // (4) Have the current cursor
                    //     Node point to new Node. 
                    cursor->prev = insertedNode;
                    // (5) Have the new Node point 
                    //     point the the cursor Node. 
                    insertedNode->next = cursor;
                    // (4) Increment the variable length to
                    //     reference the length of the list.
                    length++;
                    break;
                }
                // PROPAGATE TO THE NEXT POSSIBLE NODE. 
                cursor = cursor->next;
            }
        }
    }
}


void LinkedList::deleteNode(int index){
    // (1) If the list is empty, there wouldn't be anything to delete. 
    // (2) One thing to keep in mind, index = 0 is not the same as length = 0
    //     when implementing the delete function. 
    //
    // (3) If index == length, we would be looking at null 
    // (4) if index == length -1, we would be looking at the last node in the list.  
    if( (index >= length) ||  (index < 0) || (length == 0)){
        cout << "(Permission denied!) \nYou cannot delete a node. List is empty \n\n";
    }else{
        // Call our list object (this calls our current object)
        // and check if the object list either has a length of 1 or more. 
        LinkedList* list = this;
        // create a temp node from the 
        // declared list to check if the
        // tail exist within the list.
        Node* cursor = list->head;
        if((length == 1) && (index == 0)) {
            // (1) Since the length is 1, the head
            //     and tail are the same node to delete
            list->head = list->tail = NULL;
            // (2) Delete the only node in the list
            delete(list->head);
            delete(list->tail);
            // (3) Decrement the variable length to
            //     reference the length of the list.
            length--;
        }
        // Every condition below is if we have
        // more than one Node inside our linkedlist
        else if(length > 1){
            // If our index is looking at the
            // last element in the linked list
            if (index == length-1){
                // (1)  First point the tail
                //      node to the new Node. 
                // (1a) We are setting the previoss node
                //      to be the new tail. 
                list->tail = list->tail->prev;
                // (2)  Set the old tail to be null
                list->tail->next = NULL;
                // (3)  Delete old tail node
                delete(list->tail->next);
                // (4) Decrement the variable length to
                //     reference the length of the list.
                length--;
            }
            // If we are in the beginning of the list, 
            // delete the first node and make the next Node
            // as the new Head. 
            else if(index == 0){
                // (1)  First point the head
                //      node to the new Node. 
                // (1a) We are setting the next
                //      node to be the new head. 
                list->head = list->head->next;
                // (2) Set the old head to be NULL
                list->head->prev = NULL;
                // (3) Delete old head node
                delete (list->head->prev);
                // (4) Decrement the variable length to
                //     reference the length of the list.
                length--;
            }else{
                // This loop is used to delete any other 
                // node that is not the front or the back
                // of the list since the algorithm is already  
                // implemented in the beginning of this function.
                for (int i = 1; i < length - 1; ++i){
                    if(i == index){
                        // (1) Once our iterate varaible finds 
                        //     the location of the requested index, 
                        //     we will delete the node the cursor is currently looking 
                        //     within the list which is the index location we requested. 
                        // (2) The Node that is about to be deleted, the previous  
                        //     and next node are about to connect to each other directly. 

                        // (1) First point the previous Node
                        //     the cursor was looking to next Node
                        //     the cursor is currently looking at. 
                        cursor->prev->next = cursor->next;
                        // (2) Next point the next node the cursor 
                        //     is looking at with the previous Node
                        //     the cursor used to look at. 
                        cursor->next->prev = cursor->prev;
                        // (3) Delete the Node the
                        //     cursor is currently looking at. 
                        delete(cursor);
                        // (4) Decrement the variable length to
                        //     reference the length of the list.
                        length--;
                    }
                    // PROPAGATE TO THE NEXT POSSIBLE NODE. 
                    cursor = cursor->next;
                }
            }
        }
    }
}

// Delete the first Node in the list. 
void LinkedList::deleteFront(){
    // If the list is empty, there wouldn't be anything to delete
    if(length == 0){
        cout << "(Permission denied!) \nYou cannot delete a node. List is empty \n\n";
    }else{
        // Call our list object (this calls our current object)
        // and check if the object list either has a length of 1 or more. 
        LinkedList* list = this;
        if(length == 1){
            // (1) Since the length is 1, the head
            //     and tail are the same node to delete
            list->head = list->tail = NULL;
            // (2) Delete the only node in the list
            delete (list->head);
            delete (list->tail);
            // (3) Decrement the variable length to
            //     reference the length of the list.
            length--;
        }else{
            // (1) Have the old head point
            //     to the node in front of it. 
            //     Which is the new Head Node
            list->head = list->head->next;
            // (2) Set the old head node to null
            list->head->prev = NULL;
            // (3) Delete old head node. 
            delete (list->head->prev);
            // (4) Decrement the variable length to
            //     reference the length of the list.
            length--;
        }
    }
}
// Delete the last Node in the list. 
void LinkedList::deleteBack(){
    // If the list is empty, there wouldn't be anything to delete
    if(length == 0){
        cout << "(Permission denied!) \nYou cannot delete a node. List is empty \n\n";
    }else{
        // Call our list object (this calls our current object)
        // and check if the object list either has a length of 1 or more. 
        LinkedList* list = this;
        if(length == 1){
            // (1) Since the length is 1, the tail
            //     and head are the same node to delete
            list->tail = list->head = NULL;
            delete (list->head);
            delete (list->tail);
            // (3) Decrement the variable length to
            //     reference the length of the list.
            length--;
        }else{
            // (1) Have the old tail node point
            //     to the node in front of it. 
            //     Which is the new tail Node
            list->tail = list->tail->prev;
            // (2) Set the old tail node to null
            list->tail->next = NULL;
            // (3) Delete old tail node. 
            delete (list->tail->next);
            // (4) Decrement the variable length to
            //     reference the length of the list.
            length--;
        }
    }
}

// Printing the entire list
void LinkedList::printList(){
    // Have a cursor iterate the
    // entire list so we can print 
    // out the data within each Node. 
    LinkedList* list = this;
    Node* cursor = list->head;
    cout << "Length of the List -> (";
    cout << length << ")" << endl;
    cout << "List of Elements ---> (";
    // If the node is empty, print empty
    if(cursor == NULL){
        cout << "Empty";
    }else{
        // Propagate to each
        // node till we find NULL. 
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


int main() {
    LinkedList list;

    list.preppend(30);
    list.preppend(5);
    list.preppend(10);
    list.preppend(20);

    list.insert(100, 2);
    list.printList();

    // list.deleteNode(4);
    // list.printList();
    // list.deleteFront();
    // list.printList();
    // list.deleteFront();
    // list.printList();
    // list.deleteFront();
    // list.printList();
    // list.deleteFront();
    // list.printList();
    // list.deleteFront();
    // list.printList();

    int index, element = 0; 

    tie (index, element) = list.binarySearchList(0,  list.listLength()-1,  5);

    list.getIndex();

    cout << "(index, element): ("<< index << "," << element << ")" << endl;

    //cout << element << "\n";
    return 0;
}





