#ifndef HASH_TABLE_GUARD
#define HASH_TABLE_GUARD

typedef struct node {
	int key;
	int value;
	struct node* next;
}node;


typedef struct node node;



typedef struct hashtable {
// define the components of the hash table here (e.g. the array, bookkeeping for number of elements, etc)
	struct node* array[1009];
	int no_of_elements;
	int array_size;
	
} hashtable;

typedef int keyType;
typedef int valType;

void init(hashtable** ht);
void put(hashtable* ht, keyType key, valType value);
int get(hashtable* ht, keyType key, valType *values, int num_values);
void erase(hashtable* ht, keyType key);

#endif
