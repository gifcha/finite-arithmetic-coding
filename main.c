#include <stdio.h>
#include <stdlib.h>

// S+(P(C))*R 
// range formula, where P(C) is the previous probability of char C
//
// read file
// Create probability table
//		probability of 1.0 = UINT_MAX, all probabilities in range of [0, UINT_MAX]
// 		
// read file
// Encode


union probability_pair {
	char character;
	int probability;
};


void getRange(int* start, int* end, int probability, int R);

int main() {
	FILE* file_ptr;
	file_ptr = fopen("text.txt", "r");

	return 0;
}

union probability_pair* getProbabilityTable() {
	int n = 10;
	// allocate memory for array of probability_pair
	union probability_pair* pt = (union probability_pair*) malloc(n * sizeof *pt);

	return pt;
}

void getRange(int* start, int* end, int probability, int R) {

}
