#include "dict.h"
#include "algorithm.h"
#include "test.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	FILE* file_ptr;
	file_ptr = fopen("test.txt", "r");
	
	// run tests if "test" arg is passed
	if (argc > 1 && strcmp(argv[1], (char*) "test") == 0) {
		return runTests();
	}

	if (file_ptr == NULL) {
		printf("File pointer is NULL!\n");
		return 1;
	}

	Dict *dict_ptr = getCountDict(file_ptr);

	dict_ptr->print(dict_ptr);
	printf("total: %d\n", dict_ptr->getTotalCount(dict_ptr));

	encode(file_ptr, dict_ptr);
	

	return 0;
}
