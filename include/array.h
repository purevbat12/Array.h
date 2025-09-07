#ifndef defineArrayFunctions
	#define defineArrayFunctions
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdbool.h>
	typedef struct array{
		void *arr;
		size_t size;
		char format;
		char *label;
		size_t dimension;
	} array;
	#ifndef typeMacroLikeFunctions
		#define typeMacroLikeFunctions
		#define i(...) (&((int[]){__VA_ARGS__}))
		#define f(...) (&((double[]){__VA_ARGS__}))
		#define b(...) (&((bool[]){__VA_ARGS__}))
		#define c(...) (&((char[]){__VA_ARGS__}))
		#define s(...) ((char*[]){__VA_ARGS__})
		#define intArr sizeof(int)
		#define doubleArr sizeof(double)
		#define string sizeof(char)
		#define stringArr sizeof(char*)
		#define boolArr sizeof(bool)
	#endif
	#define a(...) ((array*[]){__VA_ARGS__})
	void emptyArr(array *arr);
	void freeArr(array *arr);
	void insertEndArr(array *arr, size_t count, void *data);
	void insertStartArr(array *arr, size_t count, void *data);
	void insertAtArr(array *arr, size_t count, void *data, size_t index);
	void removeEndArr(array *arr, size_t count);
	void removeStartArr(array *arr, size_t count);
	void removeAtArr(array *arr, const size_t count, const size_t index);
	void printArr(const array *arr, char *desc);
	void fillArr(const array *arr, void *data);
	bool includesArr(const array *arr, void *data);
	void reverseArr(array *arr);
	void assignArr(array *arr, size_t count, void *data, size_t index);
	void *atArr(const array *arr, const size_t index);
	size_t minArr(const array *arr, const size_t start, const size_t end);
	size_t maxArr(const array *arr, const size_t start, const size_t end);
	size_t sizeOfElement(char format);
	array *flattenArr(array *arr);
	int *convertIntArr(const array *arr);
	double *convertDoubleArr(const array *arr);
	char *convertCharArr(const array *arr);
	bool *convertBoolArr(const array *arr);
	char **convertStringArr(const array *arr);
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
			for(size_t i = 0; i < (size_t)count; i++){ \
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
		} \
		if(form == 'a'){ \
			array *tempArr = name; \
			size_t dimension = 1; \
			while(tempArr->format == 'a'){ \
				tempArr = *(array**)tempArr->arr; \
				dimension++; \
			} \
			name->dimension = dimension; \
		} \
		else{ \
			name->dimension = 1; \
		}
#endif
