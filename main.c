#include <stdio.h>
#include <stdlib.h>
#include "dict.h"

// S+(P(C))*R 
/* S: The cumulative sum of all previous probabilities. */
/* P(C): The probability of symbol C.*/
/* R: The range of line which is calculated by subtracting the start from the end of the line. */


// read file
// Create probability table
//		probability of 1.0 = totalCount, all probabilities in range of [0, UINT_MAX] (for now)
// 		p = count
// 	read file
// Encode
//



struct probability_pair;
struct char_count;
Dict* getCountDict(FILE* file_ptr);
int getRangeEnd(int c_start, char* sym, Dict* d, int l_start, int l_end);

int main() {
	FILE* file_ptr;
	file_ptr = fopen("text.txt", "r");
	if (file_ptr == NULL) {
		printf("File pointer is NULL!\n");
		return 1;
	}

	Dict* dict_ptr = getCountDict(file_ptr);
	
	dict_ptr->print(dict_ptr);
	printf("total: %d\n", dict_ptr->getTotalCount(dict_ptr));
	
	return 0;
}




Dict* getCountDict(FILE* file_ptr) {
	Dict* dict_ptr = new_Dict();

	// while eof not reached
	while (feof(file_ptr) == 0) {
		if (file_ptr == NULL) {
			printf("File pointer is NULL!\n");
			exit(1);
		}

		// get char from file
		char symbol = fgetc(file_ptr);

		// add char to dict
		if (dict_ptr->get(dict_ptr, symbol) != -1) {
			// add +1 to current count
			dict_ptr->insert(dict_ptr, symbol, dict_ptr->get(dict_ptr, symbol)+1);
		}
		else {
			// insert nev str with count 1
			dict_ptr->insert(dict_ptr, symbol, 1);
		}
	}

	rewind(file_ptr);
	return dict_ptr;
}

void encode(FILE* file_ptr, Dict* dict_ptr) {

	while(feof(file_ptr) == 0) {
		// get char from file
		char symbol = fgetc(file_ptr);
	}

	rewind(file_ptr);
}

char getNextDecodedChar(FILE* file_ptr, Dict* dict_ptr) {
	// variables 
	unsigned int p; // calculated probability
	unsigned int delta_p;  // by how much x increased or decreased
	unsigned int smallest_p = dict_ptr->getSmallestCount(dict_ptr); // smallest probability in dict
	char decoded_c;
	
	// read bit from file
	// if bit = 0 p = p/2
	// else p = p + p/2
	// if p < smallest_p return char
	if (p < smallest_p) {
		// get char that is in range p
	}
}







