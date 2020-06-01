#include <vector> 

using namespace std;

struct Node
{
	int data;
	Node* next;
};

class Stack{
	private:
		Node* top;

	public:
		Stack();
		Stack(int data);

		void pop();
		Node* peek();
		bool is_empty();
		void printStack();
		void push(int item);

		// 3.1: Three in One:
		// Describe how you could use a
		// single array to implement three stacks. 
		vector<Stack> threeInOne(vector<int> arr);
};