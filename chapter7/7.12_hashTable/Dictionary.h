#include <vector>
#include "list.h"

using namespace std;

class Dictionary: public LinkedList{
	private:
		int dictionarySize;
		const int tableSize = 101;
		vector<LinkedList*> hashtable;

	public:
		int hashfunction(string k);
		//unsigned int pre_hash(char* input);
		//unsigned int rotate_left(unsigned int value, int shift);

		Dictionary();
		char* lookup(Dictionary* D, string k);
		void insert(Dictionary D, char* k, char* v);
		void deleteKeyValue(Dictionary D, char* k);
		void makeEmpty(Dictionary D);
		void printlist(FILE* out, LinkedList L);
		void printDictionary(FILE* out, Dictionary D);
};