#pragma once

#include "dict.h"
#include <math.h>

// S+(P(C))*R
/* S: The cumulative sum of all previous probabilities. */
/* P(C): The probability of symbol C.*/
/* R: The range of line which is calculated by subtracting the start from the
 * end of the line. */

// read file
// Create probability table
//		probability of 1.0 = totalCount, all probabilities in range of
//[0, UINT_MAX] (for now)
// 		p = count
// 	read file
// Encode



// Returns a dict containing the count of each character found in file.
static Dict* getCountDict(FILE *file_ptr) {
	Dict* dict_ptr = new_Dict();

	// while eof not reached
	while (1) {
		if (file_ptr == NULL) {
			printf("File pointer is NULL!\n");
			exit(1);
		}

		// get char from file
		char symbol = fgetc(file_ptr);
		if (symbol == EOF) {
			break;
		}

		// add char to dict
		if (dict_ptr->get(dict_ptr, symbol) != -1) {
			// add +1 to current count
			dict_ptr->insert(dict_ptr, symbol, dict_ptr->get(dict_ptr, symbol) + 1);
		} else {
			// insert nev str with count 1
			dict_ptr->insert(dict_ptr, symbol, 1);
		}
	}

	rewind(file_ptr);
	return dict_ptr;
}

// Returns the probability for char c.
static unsigned int getProbability(Dict *dict_ptr, char c) {
	unsigned int p = 0;
	unsigned int count = dict_ptr->get(dict_ptr, c);
	if (count == -1) {
		return 0;
	}

	unsigned int total = dict_ptr->getTotalCount(dict_ptr);

	long double division = ((long double)count / (long double)total);
	division = division * pow(2, 32);

	p = (unsigned int) division;

	return p;
}

// Returns the smallest probability in dict.
static unsigned int getSmallestProbability(Dict* dict_ptr) {
	unsigned int smallest = dict_ptr->keys[0];

	for (int i=1; i<dict_ptr->size; i++) {
		char key = dict_ptr->keys[i];
		unsigned int p = getProbability(dict_ptr, key);
		if (p < smallest) {
			smallest = p;
		}
	}

	return smallest;
}

// Function for getting the probability range of char c.
// The start and end pointers contain the result after execution.
static void ProbabilityRange(unsigned int* start, unsigned int* end, Dict* dict_ptr, char c) {
	unsigned int sum = 0;

	if (getProbability(dict_ptr, c) == 0) {
		*start = 0;
		*end = 0;
		printf("ProbabilityRange not found char not in dict\n");
		return;
	}

	for (int i=0; i<dict_ptr->getIndex(dict_ptr, c); i++) {
		sum += getProbability(dict_ptr, dict_ptr->keys[i]);
	}

	*start = sum;
	*end = sum + getProbability(dict_ptr, c);
}

static void encode(FILE *file_ptr, Dict *dict_ptr) {
	FILE* encoded_file = fopen("output.fac", "w");

	// FILE LAYOUT

	// Encode first 16 bits as the amount of bits that contain the dict.
	// Dict encoding |char|count| -> |8 bit|32 bit| (max size = 8*256+32*256 = 10240 bits).
	short dict_size = sizeof(dict_ptr->keys) * 8 + sizeof(dict_ptr->values) * 8;
	fwrite(&dict_size, sizeof(dict_size), 1, encoded_file);

	// encode second 64 bits (long int) as the amount of bits that need to be read to decode

	while (feof(file_ptr) == 0) {
		char* byte_arr = (char*) "\0";
		short index = 0;
		char symbol = fgetc(file_ptr);
		int probability = getProbability(dict_ptr, symbol);

		// encoding bits to byte_arr
		while (1) {
			
		}
	}

	rewind(file_ptr);
}

static char getNextDecodedChar(FILE *file_ptr, Dict *dict_ptr) {
	// variables
	unsigned int p = pow(2, 32) -1;		// calculated probability
	unsigned int delta_p; 				// by how much x increased or decreased
	unsigned int smallest_p = getSmallestProbability(dict_ptr);
	char decoded_c;

	if (feof(file_ptr) == 0) {

	}
	// read bit from file
	// if bit = 0 p = p/2
	// else p = p + p/2
	// if p < smallest_p return char
	if (p < smallest_p) {
		// get char that is in range p
	}
}
