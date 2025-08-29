#ifndef defineArrayFunctions
	#define defineArrayFunctions
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdarg.h>
	#include <stdbool.h>
	typedef struct array{
		void *arr;
		size_t size;
		char format;
		char *label;
	} array;
	#ifndef i(...)
		#define i(...) (&((int[]){__VA_ARGS__}))
		#define f(...) (&((double[]){__VA_ARGS__}))
		#define b(...) (&((bool[]){__VA_ARGS__}))
		#define c(...) (&((char[]){__VA_ARGS__}))
		#define s(...) ((char*[]){__VA_ARGS__})
	#endif
	#define a(...) ((array*[]){__VA_ARGS__})
	#define intArr sizeof(int)
	#define doubleArr sizeof(double)
	#define string sizeof(char)
	#define stringArr sizeof(char*)
	#define boolArr sizeof(bool)
	int *convertInt(array *arr);
	double *convertDouble(array *arr);
	char *convertChar(array *arr);
	bool *convertBool(array *arr);
	char **convertString(array *arr);
	void emptyArr(array *arr);
	void freeArr(array *arr);
	void insertEnd(array *arr, size_t count, void *data);
	void insertStart(array *arr, size_t count, void *data);
	void insertAt(array *arr, size_t count, void *data, size_t index);
	void removeEnd(array *arr, size_t count);
	void removeStart(array *arr, size_t count);
	void removeAt(array *arr, size_t count, size_t index);
	void printArr(array *arr, char *desc);
	void fill(array *arr, void *data);
	bool includes(array *arr, void *data);
	void reverse(array *arr);
	void assign(array *array, size_t count, void *data, size_t index);
	void *at(array *arr, size_t index);
	size_t min(array *arr, size_t start, size_t end);
	size_t max(array *arr, size_t start, size_t end);
	size_t sizeOfElement(char format);
	#define bubbleSort(arr) (BSort(arr, "array"))
	#define selectionSort(arr) (SSort(arr, "array"))
	#define doubleSelectionSort(arr) (DSSort(arr, "array"))
	#define insertionSort(arr) (ISort(arr, "array"))
	#define binaryInsertionSort(arr) (BISort(arr, "array"))
	#define shakerSort(arr) (S1Sort(arr, "array"))
	#define quickSort(arr) (QSort(arr, "array"))
	#define mergeSort(arr) (MSort(arr, "array"))
	#define createArr(name, form, count, data) \
		array *name = malloc(sizeof(array)); \
		if(name == NULL){ \
			printf("Memory allocation failed! Exit code 2.\nExiting..."); \
			exit(2); \
		} \
		name->format = form; \
		name->size = count; \
		name->label = malloc(strlen(#name) + 1); \
		strcpy(name->label, #name); \
		{ \
			size_t pointerSize = 0; \
			for(size_t i = 0; i < count; i++){ \
				pointerSize += sizeOfElement(form); \
			} \
			name->arr = malloc(pointerSize); \
			if(name->arr == NULL){ \
				printf("Memory allocation failed for %s! Exit code 1.\nExiting...", #name); \
				exit(1); \
			} \
			if(data != NULL){ \
				memmove(name->arr, data, pointerSize); \
			} \
			else{ \
				for(size_t i = 0; i < count; i++){ \
					printf("sizeOfElement(%c) = %zu\n", form, sizeOfElement(form)); \
					memcpy((char*)name->arr + i * sizeOfElement(form), 0, sizeOfElement(form)); \
				} \
			} \
		}
	size_t sizeOfElement(char format){
		return format == 'i' ? intArr : (format == 'f') ? doubleArr : (format == 'b') ? boolArr : (format == 'c') ? string :  (format == 's') ? stringArr : 0;
	}
	size_t min(array *arr, size_t start, size_t end){
		if(arr->format == 'b'){
			printf("Cannot compare booleans.\n");
			return -1;
		}
		if(start > arr->size || end > arr->size){
			printf("Out of bound indice.\n");
			return -1;
		}
		if(start == end){
			return start;
		}
		size_t elemSize = sizeOfElement(arr->format);
		size_t result = start;
		for(size_t i = start; i <= end; i++){
			switch(arr->format){
				case 'c':
				case 'i':{
					if(*(int*)at(arr, i) < *(int*)at(arr, result)){
						result = i;
					}
					break;
				}
				case 'f':{
					if(*(double*)at(arr, i) < *(double*)at(arr, result)){
						result = i;
					}
					break;
				}
				case 's':{
					if(strlen(*(char**)at(arr, i)) > strlen(*(char**)at(arr, result))){
						result = i;
					}
					break;
				}
			}
		}
		return result;
	}
	size_t max(array *arr, size_t start, size_t end){
		if(start == end){
			printf("Indices are same.\n");
			return start;
		}
		if(start > arr->size || end > arr->size){
			printf("Out of bound indice.\n");
			return -1;
		}
		if(arr->format == 'b'){
			printf("Cannot compare booleans.\n");
			return -1;
		}
		size_t elemSize = sizeOfElement(arr->format);
		size_t result = start;
		for(size_t i = start; i <= end; i++){
			switch(arr->format){
				case 'c':
				case 'i':{
					if(*(int*)at(arr, i) > *(int*)at(arr, result)){
						result = i;
					}
					break;
				}
				case 'f':{
					if(*(double*)at(arr, i) > *(double*)at(arr, result)){
						result = i;
					}
					break;
				}
				case 's':{
					if(strlen(*(char**)at(arr, i)) > strlen(*(char**)at(arr, result))){
						result = i;
					}
					break;
				}
			}
		}
		return result;
	}
	void *at(array *arr, size_t index){
		size_t elemSize = sizeOfElement(arr->format);
		if(index > arr->size && arr->size > 0){
			printf("Out of bound in at func.\n");
			return NULL;
		}
		return (char*)(arr->arr) + elemSize * index;
	}
	void printArr(array *arr, char *desc){
		if(arr->size == 0){
			printf("%s\n%s = {}\n", desc, arr->label);
			return;
		}
		char *comma = malloc(sizeof(", "));
		if(comma == NULL){
			printf("\nMemory allocation failed! Exit code 2.\nExiting...");
			exit(2);
		}
		printf("%s\n%s = {", desc, arr->label);
		strncpy(comma, ", ", sizeof(", "));
		for(size_t i = 0; i < arr->size; i++){
			if(i + 1 == arr->size){
				char *empty = "";
				comma = realloc(comma, sizeof(""));
				if(comma == NULL){
					printf("Memory reallocation failed! Exit code 3.\nExiting...");
					exit(3);
				}
				strncpy(comma, empty, sizeof(""));
			}
			switch(arr->format){
				case 'i':{
					printf("%d%s", *((int*)(at(arr, i))), comma);
					break;
				}
				case 'f':{
					printf("%.2f%s", *((double*)(at(arr, i))), comma);
					break;
				}
				case 'c':{
					printf("%c%s", *((char*)(at(arr, i))), comma);
					break;
				}
				case 'b':{
					printf("%s%s", *((int*)(at(arr, i))) ? "true" : "false", comma);
					break;
				}
				case 's':{
					printf("\"%s\"%s", *(char**)at(arr, i), comma);
					break;
				}
			}
		}
		printf("}\n");
		free(comma);
	}
	void removeAt(array *arr, size_t count, size_t index){
		if(count == 0){
			return;
		}
		if(arr->size == 0){
			printf("An empty array.\n");
		}
		else if(arr->size == 1){
			if(arr->format == 's'){
				free(*((char**)(arr->arr)));
			}
			arr->arr = NULL;
			arr->size--;
			return;
		}
		if(count > arr->size){
			printf("Excessive count parameter.\n");
			return;
		}
		if(index >= arr->size){
			printf("Out of bound.\n");
			return;
		}
		size_t elemSize = sizeOfElement(arr->format);
		for(size_t i = index; i < arr->size - count; i++){
			memmove(at(arr, i), at(arr, i + count), elemSize);
			if(arr->format == 's'){
				free(*((char**)((char*)(arr->arr) + i * elemSize)));
			}
		}
		arr->arr = realloc(arr->arr, elemSize * (arr->size - count));
		if(arr->arr == NULL && arr->size - index == count){
			printf("Memory allocation failed! Exit code 9.\nExiting...");
			exit(9);
		}
		arr->size -= count;
	}
	void removeEnd(array *arr, size_t count){	
		if(count == 0){
			return;
		}
		if(arr->size == 0){
			printf("An empty array.\n");
			return;
		}
		if(count > arr->size){
			printf("Excessive count parameter.\n");
			return;
		}
		size_t elemSize = sizeOfElement(arr->format);
		arr->arr = realloc(arr->arr, elemSize * (arr->size - count));
		if(arr->arr == NULL && count != arr->size){
			printf("Memory allocation failed! Exit code 7.\nExiting...");
			exit(7);
		}
		arr->size -= count;
	}
	void removeStart(array *arr, size_t count){
		if(count == 0){
			return;
		}
		if(arr->size == 0){
			printf("An empty array.\n");
			return;
		}
		if(count > arr->size){
			printf("Excessive count parameter.\n");
			return;
		}
		size_t elemSize = sizeOfElement(arr->format);
		for(size_t i = 0; i < arr->size - count; i++){
			memcpy(at(arr, i), at(arr, i + count), elemSize);
		}
		arr->arr = realloc(arr->arr, elemSize * (arr->size - count));
		if(arr->arr == NULL && count != arr->size){
			printf("Memory allocation failed! Exit code 8.\nExiting...");
			exit(8);
		}
		arr->size -= count;
	}
	void insertEnd(array *arr, size_t count, void *data){
		if(count == 0){
			return;
		}
		size_t elemSize = sizeOfElement(arr->format);
		arr->arr = realloc(arr->arr, (arr->size + count) * elemSize);
		if(arr->arr == NULL){
			printf("Memory reallocation failed! Exit code 4.\nExiting...");
			exit(4);
		}
		memcpy(at(arr, arr->size), data, elemSize * count);
		arr->size += count;
	}
	void insertStart(array *arr, size_t count, void *data){
		if(count == 0){
			return;
		}
		size_t elemSize = sizeOfElement(arr->format);
		arr->arr = realloc(arr->arr, elemSize * (arr->size + count));
		if(arr->arr == NULL){
			printf("Memory reallocation failed! Exit code 5.\nExiting...");
			exit(5);
		}
		memmove((char*)arr->arr + count * elemSize, arr->arr, (count + 1) * elemSize);
		memcpy(arr->arr, data, elemSize * count);
		arr->size += count;
	}
	void insertAt(array *arr, size_t count, void *data, size_t index){
		if(count == 0){
			return;
		}
		size_t elemSize = sizeOfElement(arr->format);
		if(index > arr->size){
			printf("Out of bounds index.\n");
			return;
		}
		arr->arr = realloc(arr->arr, (arr->size + count) * elemSize);
		if(arr->arr == NULL){
			printf("Memory reallocation failed! Exit code 6.\nExiting...");
			exit(6);
		}
		memmove((char*)arr->arr + (index + count) * elemSize, (char*)arr->arr + index * elemSize, (arr->size - index) * elemSize);
		memmove((char*)arr->arr + index * elemSize, data, elemSize * count);
		arr->size += count;
	}
	void fill(array *arr, void *data){
		size_t elemSize = sizeOfElement(arr->format);
		if(arr->size == 0){
			printf("An empty array.\n");
			return;
		}
		for(size_t i = 0; i < arr->size; i++){
			memcpy(at(arr, i), data, elemSize);
		}
	}
	void reverse(array *arr){
		if(arr->size <= 1){
			return;
		}
		size_t elemSize = sizeOfElement(arr->format);
		size_t halfIndex = arr->size / 2;
		void *temp = malloc(elemSize);
		if(temp == NULL){
			printf("Memory allocation failed! Exit code 9.\nExiting...");
			exit(1);
		}
		for(size_t i = 0; i < halfIndex; i++){
			memcpy(temp, at(arr, i), elemSize);
			assign(arr, 1, at(arr, arr->size - i - 1), i);
			assign(arr, 1, temp, arr->size - i - 1);
		}
	}
	bool includes(array *arr, void *data){
		size_t elemSize = sizeOfElement(arr->format);
		if(arr->size == 0){
			printf("An empty array.\n");
			return false;
		}
		bool isIncluded = false;
		for(size_t i = 0; i < arr->size; i++){
			switch(arr->format){
				case 'i':
					if(*((int*)(data)) == *((int*)at(arr, i))){
						isIncluded = true;
					}
					break;
				case 'f':
					if(*((double*)(data)) == *((double*)at(arr, i))){
						isIncluded = true;
					}
					break;
				case 'b':
					if(*((bool*)(data)) == *((bool*)at(arr, i))){
						isIncluded = true;
					}
					break;
				case 'c':
					if(*((char*)(data)) == *((char*)at(arr, i))){
						isIncluded = true;
					}
					break;
				case 's':
					if(strcmp(((char**)(arr->arr))[i], *(char**)(data)) == 0){
						isIncluded = true; 
					}
					break;
			}
		}
		return isIncluded;
	}
	void assign(array *arr, size_t count, void *data, size_t index){
		size_t elemSize = sizeOfElement(arr->format);
		if(index > arr->size){
			printf("Out of bound.\n");
			return;
		}
		size_t moreThanDifference = 0;
		if(index + count >= arr->size){
			moreThanDifference = index + count - arr->size;
			arr->arr = realloc(arr->arr, elemSize * (index + count));
			if(arr->arr == NULL){
				printf("Memory allocation failed! Exit code 10.\nExiting...");
				exit(10);
			}
			arr->size += moreThanDifference;
		}
		memcpy(at(arr, index), data, elemSize * count);
	}
	void emptyArr(array *arr){
		if(arr->size == 0){
			return;
		}
		removeAt(arr, arr->size - 1, 0);
		arr->size = 0;
	}
	void freeArr(array *arr){
		arr->size = 0;
		free(arr->arr);
		free(arr->label);
		free(arr);
	}
	int *convertInt(array *arr){
		if(arr->format != 'i'){
			printf("Wrong data type %c.\n", arr->format);
			return;
		}
		size_t elemSize = sizeOfElement(arr->format);
		int *a = malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	double *convertDouble(array *arr){
		if(arr->format != 'f'){
			printf("Wrong data type %c.\n", arr->format);
			return;
		}
		size_t elemSize = sizeOfElement(arr->format);
		double *a = malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	char *convertChar(array *arr){
		if(arr->format != 'c'){
			printf("Wrong data type %c.\n", arr->format);
			return;
		}
		size_t elemSize = sizeOfElement(arr->format);
		char *a = malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	bool *convertBool(array *arr){
		if(arr->format != 'b'){
			printf("Wrong data type %c.\n", arr->format);
			return;
		}
		size_t elemSize = sizeOfElement(arr->format);
		bool *a = malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	char **convertString(array *arr){
		if(arr->format != 's'){	
			printf("Wrong data type %c.\n", arr->format);
			return;
		}
		size_t elemSize = sizeOfElement(arr->format);
		char **a = malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	#include <sort.h>
#endif
