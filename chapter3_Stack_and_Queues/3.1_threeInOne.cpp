#include <vector>
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



vector<Stack> threeInOne(vector<int> arr){
	Stack element;
	int outOfBound = 0;
	int innerBound = 0;
	int stackIndex = 0;
	int divideCounter = 0;
	vector<Stack> stackVec;
	int dividedNum = arr.size() / 3;
	int modulasNum = arr.size() % 3;
	int dividedNumLength = dividedNum;
	if(dividedNum == 0){
		if (modulasNum == 1){
			stackVec.push_back(element);
			stackVec[stackIndex].push(arr[0]);
		}
		if (modulasNum == 2){
			stackVec.push_back(element);
			stackVec.push_back(element);
			stackVec[stackIndex].push(arr[0]);
			stackVec[stackIndex+1].push(arr[1]);
		}
	}else{
		if (modulasNum == 2){
			dividedNum++;
		}
		stackVec.push_back(element);
		for (int i = 0; i < arr.size(); i++){
			if(modulasNum == 1){
				outOfBound = dividedNumLength + i;
				if (arr.size() == outOfBound){
					dividedNum++;
				}
			}
			if (modulasNum == 2){
				innerBound = i + dividedNumLength;
				if(innerBound == arr.size()){
					dividedNum--;
					divideCounter--;
				}
			}
			if(dividedNum == divideCounter){
				stackIndex++;
				divideCounter = 0;
				stackVec.push_back(element);
			}
			divideCounter++;
			stackVec[stackIndex].push(arr[i]);

		}
	}
	return stackVec;
}



int main(){
	vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8};
	vector<Stack> v = threeInOne(arr);

	for (int i = 0; i < v.size(); ++i)
	{
		v[i].printStack();
	}
}











