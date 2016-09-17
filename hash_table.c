	#include "hash_table.h"
	#include<stdlib.h>
	#include<stdio.h>
	// insert an element in linked list
node* insert(node* head, int key, int value)
{
	node* newnode = (node*)malloc(sizeof(node));
	newnode->key = key;
	newnode->value = value;
		
	newnode->next = head;
	head = newnode;
	
	return head;
}
	// delete an element from linked list
node* delete(node* head, int key)
{
	node* temp = head;
	node* del_node = NULL;
	if(!head)
		return head;
	if(head->key == key)
	{
		del_node = head;
		head = head->next;
	}
	while(temp->next!=NULL && temp->next->key != key)
	{
		temp = temp->next;
	}
	if(temp->next != NULL)
	{
		del_node = temp->next;
		temp->next = temp->next->next;
	}
	free(del_node);
	return head;
}

// initialize the components of the hashtable
void init(hashtable** ht) {
    // This line tells the compiler that we know we haven't used the variable
    // yet so don't issue a warning. You should remove this line once you use
    // the parameter.
    // (void) ht;
	
	*ht = (hashtable*) malloc(sizeof(hashtable));
	
	int array_size = 1009;
	(*ht)->array_size = array_size;
	for (int i=0; i<array_size; i++)
	{
		(*ht)->array[i] = NULL;	
	}
	(*ht)->no_of_elements = 0;
	
}

// insert a key-value pair into the hash table
void put(hashtable* ht, keyType key, valType value) {
    int N = ht->array_size;
	int slot = key%N;
	ht->array[slot] = insert(ht->array[slot], key, value); 
	//printf("key: %d, slot: %d", key, slot);
	ht->no_of_elements +=1;
}

// get entries with a matching key and stores the corresponding values in the
// values array. The size of the values array is given by the parameter
// num_values. If there are more matching entries than num_values, they are not
// stored in the values array to avoid a buffer overflow. The function returns
// the number of matching entries. If the return value is greater than
// num_values, the caller can invoke this function again (with a larger buffer)
// to get values that it missed during the first call. 
int get(hashtable* ht, keyType key, valType *values, int num_values) {
    (void) ht;
    (void) key;
    (void) values;
    (void) num_values;
	int N = ht->array_size;
	int slot = key%N;
	
	int i = 0;
	node* temp = ht->array[slot];
	while(temp!= NULL)
	{
		if(temp->key == key)
		{
			values[i] = temp->value;
			
			i=i+1;
		}
		temp = temp->next;
	}
    return i;
}

// erase a key-value pair from the hash talbe
void erase(hashtable* ht, keyType key) {
    (void) ht;
    (void) key;
	int N = ht->array_size;
	int slot = key%N;
	node* delnode = NULL;
	
	node* temp = ht->array[slot];
	if(temp != NULL && temp->key == key)
	{
		delnode = temp;
		ht->array[slot]= ht->array[slot]->next;
		free(delnode);
	}
	else
	{
		while(temp->next == NULL)
		{
			if(temp->next->key == key)
			{
				delnode = temp->next;
				temp->next = temp->next->next;
				free(delnode);
				break;
			}
			temp = temp->next;
		}
	}
	

}
