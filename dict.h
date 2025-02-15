#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 


#define MAX_SIZE 256 // Maximum number of elements in the map 

// TODO
// remake dict to contain struct with probability range (start, end)
// need dict that contains character with ranges
//

typedef struct Dict Dict;
struct Dict {
	int size; // Current number of elements in the map 
	char keys[MAX_SIZE]; // Array to store the keys 
	int values[MAX_SIZE]; // Array to store the values 

	int (*getIndex)(Dict* self, char key);
	void (*insert)(Dict* self, char key, int value);
	int (*get)(Dict* self, char key);
	void (*print)(Dict* self);
	int (*getTotalCount)(Dict* self);
	unsigned int (*getSmallestCount)(Dict* self);
};



// Function to get the index of a key in the keys array 
static int dict_getIndex(Dict* self, char key) { 
	for (int i = 0; i < self->size; i++) { 
		if (self->keys[i] == key) { 
			return i; 
		} 
	} 
	return -1; // Key not found 
} 

// Function to insert a key-value pair into the map 
static void dict_insert(Dict* self, char key, int value) { 
	int index = self->getIndex(self, key); 
	if (index == -1) { // Key not found 
		self->keys[self->size] = key;
		self->values[self->size] = value; 
		self->size = self->size + 1; 
	} 
	else { // Key found 
		self->values[index] = value; 
	} 
} 

// Function to get the value of a key in the map 
static int dict_get(Dict* self, char key) { 
	int index = self->getIndex(self, key); 
	if (index == -1) { // Key not found 
		return -1;
	} 
	else { // Key found 
		return self->values[index]; 
	} 
} 

// Function to print the map 
static void dict_printMap(Dict* self) { 
	for (int i = 0; i < self->size; i++) { 
		char key_str[3] = {'\0', '\0', '\0'}; // without setting \0 chars from previous iterations stay
		key_str[0] = self->keys[i];

		// convert special symbols for printing
		switch (key_str[0]) {
			case '\n':
				strcpy(key_str, (char*) "\\n");
				break;
			case '\r':
				strcpy(key_str, (char*) "\\r");
				break;
			default:
				break;
		}

		printf("%s: %d\n", key_str, self->values[i]); 
	} 
} 

static int dict_getTotalCount(Dict* self) {
	int total = 0;

	for (int i = 0; i < self->size; i++) { 
		total += self->values[i];
	} 

	return total;
}

static unsigned int dict_getSmallestCount(Dict* self) {
	unsigned int smallest = self->values[0];

	for (int i = 0; i < self->size; i++) { 
		if (smallest > self->values[i]) {
			smallest = self->values[i];
		}
	} 

	return smallest;
}



static Dict* new_Dict() {
	// initializes and allocated dict in heap
	Dict* d = (Dict*) malloc(sizeof(Dict));
	d->getIndex = dict_getIndex;
	d->insert = dict_insert;
	d->get = dict_get;
	d->print = dict_printMap;
	d->getTotalCount = dict_getTotalCount;
	d->getSmallestCount = dict_getSmallestCount;

	d->size = 0;
	return d;
}

