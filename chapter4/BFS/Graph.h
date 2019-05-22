

struct Node {
	int data = 0;
	Node *next;
	Node *prev;
};

class LinkedList{
    private:
        int length; 
        Node *head; 
        Node *tail; 

    public:
    	LinkedList();
    	void append(int element);
    	void printList();
};


class Graph: public LinkedList{
	private:
		int size;
		int source;
		int order;
		LinkedList* adj;
		char* color;
		int* parent;
		int* distance;
	public:
		Graph newGraph(int n);
		void freeGraph(Graph* pG);
		int getOrder(Graph G);
		int getSize(Graph G);
		int getSource(Graph G);
		int getParent(Graph G, int u);
		int getDist(Graph G, int u);
		void getPath(List L, Graph G, int u);
		void makeNull(Graph G);
		void addEdge(Graph G, int u, int v);
		void addArc(Graph G, int u, int v);
		void BFS(Graph G, int s);
		void printGraph(FILE* out, Graph G);
		void printPath(Graph G, FILE* out, int s, int x);

};









