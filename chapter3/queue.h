struct Node
{
	int data;
	Node* next;
};


class queue{
	private:
		Node* first;
		Node* last;
	public:
		queue();
		queue(int data);

		void remove();
		Node* peek();
		bool is_empty();
		void printQueue();
		void push(int item);
};