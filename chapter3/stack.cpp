#include "stack.h"
#include <iostream>

using namespace std;

Stack::Stack(){
	top = NULL;
}


Stack::Stack(int data){
	Node *firstNode = new Node();
	top = firstNode;
}


void Stack::pop(){
	Stack* list = this;
	if(!is_empty()){
		list->top = list->top->next;
	}else{
		cout << "Already empty!" << endl;
	}
}


Node* Stack::peek(){
	Stack* list = this;
	if(!is_empty()){
		return list->top;
	}return NULL;
}


bool Stack::is_empty(){
	Stack* list = this;
	Node* cursor = list->top;
	if(cursor != NULL){
		return false;
	}return true;
}


void Stack::push(int item){
	Stack* list = this;
	Node* topNode = new Node();
	topNode->data = item;
	if(!is_empty()){
		topNode->next = list->top;
		list->top = topNode;
	}else{
		list->top = topNode;
	}
}

void Stack::printStack(){
	Stack* list = this;
	Node* cursor = list->top;
	if(!is_empty()){
		while(cursor != NULL){
			cout << cursor->data << endl;
			cursor = cursor->next;
		}cout << endl;
	}
}

int main(){
	Stack list(0);
	list.push(1);
	list.push(2);
	list.push(3);
	list.printStack();
	list.pop();	
	// list.pop();
	// list.pop();
	// list.pop();
	list.printStack();
	return 0;
}

