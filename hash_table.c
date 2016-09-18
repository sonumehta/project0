	#include "hash_table.h"
	#include<stdlib.h>
	#include<stdio.h>
	// insert an element in linked list


node* insert(node* head, int key, int value)
{
	if(head && !(head->filled))
	{
		head->key[1] = key;
		head->value[1] = value;
		head->filled = 1;
		return head;
	}
	
	node* newnode = (node*)malloc(sizeof(node));
	newnode->key[0] = key;
	newnode->value[0] = value;
	newnode->filled = 0;	
		
	newnode->next = head;
	head = newnode;
	
	return head;
}
	// delete a key from linked list
node* delete_key(node* head, int key)
{
	
	node* del_node = NULL;
	if(!head)
		return head;
	if(head->key[0] == key)
	{
		if((!(head->filled)) || (head->filled && head->key[1] == key))
		{
			del_node = head;
			head = head->next;
			free(del_node);
		}
		else
		{
			head->key[0] = head->key[1];
			head->value[0] = head->value[1];
			head->filled = 0;
		}
		
	}
	else if(head->filled && head->key[1] == key)
	{
		head->filled = 0;
	}
	
	node* temp = head;
	while(temp && temp->next)
	{
		if(temp->next->key[0] == key)
		{
			if(temp->next->filled)
			{
				if(temp->next->key[1] == key)
				{
					del_node = temp->next;
					temp->next = temp->next->next;
					free(del_node);
				}
				else
				{
					temp->next->key[0] = temp->next->key[1];
					temp->next->value[0] = temp->next->value[1];
				}
			}
		}
		else if(temp->next->filled && temp->next->key[1] == key)
		{
			temp->next->filled = 0;
		}
			
		temp = temp->next;
	}
	
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
	(*ht)->array = malloc(sizeof(node*)* array_size);
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
	
	//printf("key: %d, slot: %d", ht->array1[slot]->key, ht->array1[slot]->value);
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
		if(temp->key[0] == key)
		{
			values[i] = temp->value[0];
			i=i+1;
			if(temp->filled && temp->key[1] == key)
			{
				values[i] = temp->value[1];
				i=i+1;
			}
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
	
	ht->array[slot] = delete_key(ht->array[slot], key);
	
	ht->no_of_elements -= 1;
	

}
