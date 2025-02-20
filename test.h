#pragma once

#include <math.h>
#include <stdio.h>
#include "dict.h"
#include "algorithm.h"


static int test_getCountDict(FILE* file_ptr);
static int test_getProbability(FILE* file_ptr);

static int runTests() {
	char* result[2] = {(char*)"passed", (char*)"failed"};
	FILE* file_ptr = fopen("test.txt", "r");

	printf("Running tests!\n");
	printf("getCountDict: %s\n", result[test_getCountDict(file_ptr)]);
	printf("getProbability: %s\n", result[test_getProbability(file_ptr)]);


	return 0;
}

static int test_getCountDict(FILE* file_ptr) {
	Dict *dict_ptr = getCountDict(file_ptr);

	char expected_keys[] = "abcd\n";

	if (sizeof(expected_keys) != dict_ptr->size+1) {
		return 1;
	}

	unsigned int s1_sum = 0;
	unsigned int s2_sum = 0;
	for (int i=0; i<dict_ptr->size; i++) {
		s1_sum = s1_sum + (int) expected_keys[i];
		s2_sum = s2_sum + (int) dict_ptr->keys[i];
	}

	if (s1_sum == s2_sum) {
		return 0;
	}

	return 1;
}

static int test_getProbability(FILE* file_ptr) {
	Dict *dict_ptr = getCountDict(file_ptr);
	unsigned int p = getProbability(dict_ptr, 'a');
	unsigned int p_fail = getProbability(dict_ptr, 'f');

	int acceptable_error = 3;

	if ((p - 3 < 954437176 || p + 3 > 954437176) && p_fail == 0) {
		return 0;
	}


	return 1;
}







