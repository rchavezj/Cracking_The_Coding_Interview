#include "queue.h"
#include <iostream>

using namespace std;

queue::queue(){
	first = last = NULL;
}

queue::queue(int data){
	Node* firstNode = new Node();
	firstNode->data = data;
	first = last = firstNode;
}

void queue::remove(){
	queue* list = this;
	Node* firstOut = list->first;
	if(!is_empty()){
		list->first = list->first->next;
		// delete(firstOut);
	}else{
		cout << "Already empty" << endl;
	}
}


Node* queue::peek(){
	queue* list = this;
	if(!is_empty()){
		return list->first;
	}return NULL;
}

bool queue::is_empty(){
	queue* list;
	if(list->last != NULL){
		return false;
	}return true;
}

void queue::printQueue(){
	queue* list = this;
	Node* cursor = list->first;
	while(cursor != NULL) {
	    cout << cursor->data;
	    cout << " ";
	    cursor = cursor->next;
	}cout << endl;
}


void queue::push(int item){
	queue* list = this;
	Node* newNode = new Node();
	newNode->data = item;
	if(!is_empty()){
		list->last->next = newNode;
		list->last = newNode;
	}else{
		first = last = newNode;
	}
}



int main(){
	queue list;
	list.push(1);
	list.push(2);
	list.push(3);
	list.printQueue();
	list.remove();
	//list.remove();
	list.printQueue();

}




