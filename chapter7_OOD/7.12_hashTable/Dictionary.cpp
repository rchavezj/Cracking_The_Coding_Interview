#include <vector>
#include "Dictionary.h"

#define MAX_LEN 180

struct Node {
    char* key;
    char* value;
    Node *next;
    Node *prev;
};

Dictionary::Dictionary(){
	dictionarySize = 0;
	for (int i  = 0; i < tableSize; i++){
		hashtable[i] = new LinkedList();
	}
}
// Returns an array location for a given item key.
int Dictionary::hashfunction(string k){
    int value = 0;
    for(int i = 0; i < k.size(); i++){
        value += k[i];
    }
    return (value * k.size() ) % dictionarySize;
}

char* lookup(Dictionary* D, string k){
	Node *cursor = D->hashtable[hashfunction(k)]->head;
	while(cursor != NULL){
		if(strcmp(cursor->key, k) == 0){
			return cursor->value;
		}
	}
}