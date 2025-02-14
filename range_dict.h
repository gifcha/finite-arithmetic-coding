#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 


#define MAX_SIZE (sizeof(char) * 8) // Maximum number of elements in the map 

// TODO
// remake dict to contain struct with probability range (start, end)
// need dict that contains character with ranges
//

typedef struct Range Range;
struct Range {
	unsigned int start;
	unsigned int end;
};

typedef struct Dict Dict;
struct Dict {
	int size; // Current number of elements in the map 
	char keys[MAX_SIZE]; // Array to store the keys 
	Range values[MAX_SIZE]; // Array to store the values 

	int (*getIndex)(Dict* self, char key);
	void (*insert)(Dict* self, char key, Range value);
	Range (*get)(Dict* self, char key);
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
static void dict_insert(Dict* self, char key, Range value) { 
    int index = self->getIndex(self, key); 
    if (index == -1) { // Key not found 
        self->keys[self->size] = key;
        self->values[self->size] = value; 
        self->size = self->size + 1; 
		printf("%d\n", self->size);
    } 
    else { // Key found 
        self->values[index] = value; 
    } 
} 

// Function to get the value of a key in the map 
static Range dict_get(Dict* self, char key) { 
    int index = self->getIndex(self, key); 
    if (index == -1) { // Key not found 
        throw "dict_get(key) Key not found!" ; 
    } 
    else { // Key found 
        return self->values[index]; 
    } 
} 
  
// Function to print the map 
static void dict_printMap(Dict* self) { 
    for (int i = 0; i < self->size; i++) { 
		char* key_str = (char*) malloc(2);
		key_str[0] = self->keys[i];

		// convert special symbols for printing
		switch (key_str[0]) {
		  case '\n':
			key_str = (char*) "\\n";
			break;
		  case '\r':
			key_str = (char*) "\\r";
			break;
		}

        printf("%s: [%d, %d]\n", key_str, self->values[i].start, self->values[i].end); 
    } 
} 

static int dict_getTotalCount(Dict* self) {
	int total = 0;

    for (int i = 0; i < self->size; i++) { 
		total += self->values[i].end;
    } 

	return total;
}

static unsigned int dict_getSmallestCount(Dict* self) {
	unsigned int smallest = self->values[0].end - self->values[0].start;

	for (int i = 0; i < self->size; i++) { 
		if (smallest > self->values[i].end - self->values[i].start) {
			smallest = self->values[i].end - self->values[i].start;
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
 
