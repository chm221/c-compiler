/*
Program Translation 4503
Assignment 2 Parser
Chelsea McFarland
3/3/16 

This hash table is used to store the symbol table. It is made up of 
nodes, representing variables. Each has a key, the name of the variable;
a type, the type of variable; and a value, the value of the variable.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include "hash.h"

struct node_s {
    struct node_s *next;
    char *key;
    int value;
    int type;
};
 
 struct hashtable_s {
    int size;           /* size of the pointer table */
    int n;              /* number of elements stored */
    struct node_s **table;
};

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)

//internal create function
hashtable_t initialize_table(int size){
	hashtable_t h;
	int i;
	h = malloc(sizeof(*h));
	
	assert(h != 0);
	
	h->size = size;
	h->n = 0;
	h->table = malloc(sizeof(node_t *) * h->size);
	
	assert(h->table != 0);
	
	for(i = 0; i < h->size; i++)
		h->table[i] = 0;
	
	return h;
}

//create initial table
hashtable_t table_create(void){
	return initialize_table(INITIAL_SIZE);
}

//destroy table
void destroy(hashtable_t h){
	int i;
	node_t *n;
	node_t *next;
	
	for(i = 0; i <h->size; i++){
		for(n = h->table[i]; n != 0; n = next){
			next = n->next;
			
			free(n->key);
			free(n);
		}
	}
	
	free(h->table);
	free(h);
}

#define MULTIPLIER (97)

static unsigned long hash_function(const char *s){
	unsigned const char *us;
	unsigned long k;
	
	k = 0;
	
	for(us = (unsigned const char *) s; *us; us++)
		k = k * MULTIPLIER + *us;
		
	return k;
}

static void grow(hashtable_t h){
	hashtable_t h2;
	struct hashtable_s swap;
	int i;
	node_t *n;
	
	h2 = initialize_table(h->size * GROWTH_FACTOR);
	
	for(i = 0; i < h->size; i += 1){
		for(n = h->table[i]; n != 0; n = n->next){
			insert(h2, n->key, n->value, n->type);
		}
	}
	
	swap = *h;
	*h = *h2;
	*h2 = swap;
	
	destroy(h2);
}

void insert(hashtable_t h, const char *key, int value, int type){
	node_t *n;
	unsigned long k;
	assert(key);
	assert(value);
	
	n = malloc(sizeof(*n));
	
	assert(n);
	
	n->key = strdup(key);
	n->value = value;
	n->type = type;
	
	k = hash_function(key) % h->size;
	
	n->next = h->table[k];
	h->table[k] = n;
	
	h->n++;
	
	if(h->n >= h->size * MAX_LOAD_FACTOR)
		grow(h);
}

void add_value(hashtable_t h, const char *key, int value){
	node_t *n;
	assert(key);

	h->table[hash_function(key) % h->size]->value = value;
}

int search_hash(hashtable_t h, const char *key){
	node_t *n;
	
	for(n = h->table[hash_function(key) % h->size]; n != 0; n = n->next){
		if(!strcmp(n->key, key)){
			return n->value;
		}
	}
	
	return 0;
}

void print_hash(hashtable_t h, const char *key){
	FILE *fp;
	fp = fopen("output.txt", "w");
	fprintf(fp, "Type ID Value\n");
	int i;
	node_t *n;
	
	for(i = 0; i < h->size; i += 1){
		n = h->table[i];
		if(n != 0){
			if(n->type == 12)
				fprintf(fp, "int ");
			fprintf(fp, "%s %i\n", n->key, n->value);
		}
	}
}