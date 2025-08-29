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
	#endif
	#define a(...) ((array*[]){__VA_ARGS__})
	#define intArr sizeof(int)
	#define doubleArr sizeof(double)
	#define string sizeof(char)
	#define stringArr sizeof(char*)
	#define boolArr sizeof(bool)
	static inline void emptyArr(array *arr);
	static inline void freeArr(array *arr);
	static inline void insertEnd(array *arr, size_t count, void *data);
	static inline void insertStart(array *arr, size_t count, void *data);
	static inline void insertAt(array *arr, size_t count, void *data, size_t index);
	static inline void removeEnd(array *arr, size_t count);
	static inline void removeStart(array *arr, size_t count);
	static inline void removeAt(array *arr, const size_t count, const size_t index);
	static inline void printArr(const array *arr, char *desc);
	static inline void fill(const array *arr, void *data);
	static inline bool includes(const array *arr, void *data);
	static inline void reverse(array *arr);
	static inline void assign(array *arr, size_t count, void *data, size_t index);
	static inline void *at(const array *arr, const size_t index);
	static inline size_t min(const array *arr, const size_t start, const size_t end);
	static inline size_t max(const array *arr, const size_t start, const size_t end);
	static inline size_t sizeOfElement(char format);
	static inline array *flatten(array *arr);
	static inline int *convertInt(const array *arr);
	static inline double *convertDouble(const array *arr);
	static inline char *convertChar(const array *arr);
	static inline bool *convertBool(const array *arr);
	static inline char **convertString(const array *arr);
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
	static inline size_t sizeOfElement(const char format){
		return format == 'i' ? intArr : (format == 'f') ? doubleArr : (format == 'b') ? boolArr : (format == 'c') ? string :  (format == 's') ? stringArr : (format == 'a') ? sizeof(array*) : 0;
	}
	static inline size_t min(const array *arr, const size_t start, const size_t end){
		if(arr->format == 'b' || arr->format == 'a'){
			printf("Cannot compare booleans and arrays.\n");
			return -1;
		}
		if(start > arr->size || end > arr->size){
			printf("Out of bound indices.\n");
			return -1;
		}
		if(start == end){
			return start;
		}
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
				default:{
					printf("Not supported data type %c.\n", arr->format);
					return -1;
				}
			}
		}
		return result;
	}
	static inline size_t max(const array *arr, const size_t start, const size_t end){
		if(start == end){
			printf("Indices are same.\n");
			return start;
		}
		if(start > arr->size || end > arr->size){
			printf("Out of bound indices.\n");
			return -1;
		}
		if(arr->format == 'b' || arr->format == 'a'){
			printf("Cannot compare booleans and arrays.\n");
			return -1;
		}
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
				default: {
					printf("Not supported data type %c.\n", arr->format);
					return -1;
				}
			}
		}
		return result;
	}
	static inline void *at(const array *arr, const size_t index){
		const size_t elemSize = sizeOfElement(arr->format);
		if(index > arr->size && arr->size > 0){
			printf("Out of bound in at func.\n");
			return NULL;
		}
		return (char*)(arr->arr) + elemSize * index;
	}
	static inline void printArr(const array *arr, char *desc){
		if(arr->size == 0){
			printf("Description: %s\n%s = {}\n", desc, arr->label);
			return;
		}
		if(!strcmp(desc, "R")){
			printf("{ ");
		}
		else{
			printf("Description: %s\n%s = { ", desc, arr->label);
		}
		for(size_t i = 0; i < arr->size; i++){
			switch(arr->format){
				case 'i':{
					printf("%d ", *((int*)(at(arr, i))));
					break;
				}
				case 'f':{
					printf("%.2f ", *((double*)(at(arr, i))));
					break;
				}
				case 'c':{
					printf("%c ", *((char*)(at(arr, i))));
					break;
				}
				case 'b':{
					printf("%s ", *((int*)(at(arr, i))) ? "true" : "false");
					break;
				}
				case 's':{
					printf("\"%s\" ", *(char**)at(arr, i));
					break;
				}
				case 'a':{
					const array *temp = arr;
					printArr(*((array**)at(temp, i)), "R");
					break;
				}
				default:{
					printf("Data type not supported or invalid format.\n format = %c.", arr->format);
					return;
				}
			}
		}
		if(!strcmp(desc, "R")){
			printf("} "); 
		}
		else{
			printf("}\n");
		}
	}
	static inline void removeAt(array *arr, const size_t count, size_t index){
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
		const size_t elemSize = sizeOfElement(arr->format);
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
	static inline void removeEnd(array *arr, const size_t count){
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
		const size_t elemSize = sizeOfElement(arr->format);
		arr->arr = realloc(arr->arr, elemSize * (arr->size - count));
		if(arr->arr == NULL && count != arr->size){
			printf("Memory allocation failed! Exit code 7.\nExiting...");
			exit(7);
		}
		arr->size -= count;
	}
	static inline void removeStart(array *arr, size_t count){
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
		const size_t elemSize = sizeOfElement(arr->format);
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
	static inline array *deepCopyArr(const array *data){
		if(data == NULL){
			printf("Data is NULL.\n");
			return NULL;
		}
		array *copy = malloc(sizeof(array));
		if(copy == NULL){
			printf("Memory allocation failed! Exit code 107.\nExiting...");
			exit(107);
		}
		copy->format = data->format;
		copy->dimension = data->dimension;
		copy->label = malloc(strlen(data->label) + 1);
		copy->size = data->size;
		strcpy(copy->label, data->label);
		const size_t elemSize = sizeOfElement(copy->format);
		if(copy->format == 'a'){
			copy->arr = malloc(copy->size * elemSize);
			if(copy->arr == NULL){
				printf("Memory allocation failed! Exit code 108.\nExiting...");
				exit(108);
			}
			for(size_t i = 0; i < copy->size; i++){
				((array**)copy->arr)[i] = deepCopyArr(((array**)data->arr)[i]);
			}
		}
		else{
			copy->arr = malloc(copy->size * elemSize);
			if(copy->arr == NULL){
				printf("Memory allocation failed! Exit code 109.\nExiting...");
				exit(109);
			}
			memcpy(copy->arr, data->arr, copy->size * elemSize);
		}
		return copy;
	}
	static inline void insertEnd(array *arr, const size_t count, void *data){
		insertAt(arr, count, data, arr->size - 1);
	}
	static inline void insertStart(array *arr, const size_t count, void *data){
		insertAt(arr, count, data, 0);
	}
	static inline void insertAt(array *arr, const size_t count, void *data, const size_t index){
		if(count == 0){
			return;
		}
		if(arr->dimension > 1 && (*(array**)data)->dimension != arr->dimension - 1){
			printf("Not compatible data.\n");
			return;
		}
		if(index >= arr->size && arr->size != 0){
			printf("Out of bounds index.\n");
			return;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		arr->arr = realloc(arr->arr, (arr->size + count) * elemSize);
		if(arr->arr == NULL){
			printf("Memory reallocation failed! Exit code 6.\nExiting...");
			exit(6);
		}
		if(arr->format == 'a'){
			memmove((char*)arr->arr + (index + count + 1) * elemSize, (char*)arr->arr + (index + 1) * elemSize, (arr->size - index - 1) * elemSize);
			for (size_t i = 0; i < count; i++) {
				array *copied = deepCopyArr(((array**)data)[i]);
				((array**)arr->arr)[index + i + 1] = copied;
			}
		}
		else{
			memmove((char*)arr->arr + (index + count + 1) * elemSize, (char*)arr->arr + (index + 1) * elemSize, (arr->size - index - 1) * elemSize);
			memmove((char*)arr->arr + (index + 1) * elemSize, data, count * elemSize);
		}
		arr->size += count;
	}
	static inline void fill(const array *arr, void *data){
		if(arr->dimension > 1 && (*(array**)data)->dimension != arr->dimension - 1){
			printf("Not compatible datatype.\n");
			return;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		if(arr->size == 0){
			printf("An empty array.\n");
			return;
		}
		for(size_t i = 0; i < arr->size; i++){
			memcpy(at(arr, i), data, elemSize);
		}
	}
	static inline void reverse(array *arr){
		if(arr->size <= 1){
			return;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		const size_t halfIndex = arr->size / 2;
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
	static inline bool includes(const array *arr, void *data){
		if(arr->size == 0){
			printf("An empty array.\n");
			return false;
		}
		bool isIncluded = false;
		for(size_t i = 0; i < arr->size; i++){
			switch(arr->format){
				case 'i':{
					if(*((int*)(data)) == *((int*)at(arr, i))){
						isIncluded = true;
					}
					break;
				}
				case 'f':{
					if(*((double*)(data)) == *((double*)at(arr, i))){
						isIncluded = true;
					}
					break;
				}
				case 'b':{
					if(*((bool*)(data)) == *((bool*)at(arr, i))){
						isIncluded = true;
					}
					break;
				}
				case 'c':{
					if(*((char*)(data)) == *((char*)at(arr, i))){
						isIncluded = true;
					}
					break;
				}
				case 's':{
					if(strcmp(((char**)(arr->arr))[i], *(char**)(data)) == 0){
						isIncluded = true; 
					}
					break;
				}
				case 'a':{
					if(*(array**)data == *(array**)at(arr, i)){
						isIncluded = true;
					}
				}
				default: {
					printf("Data type not supported or invalid format.\n format = %c\n", arr->format);
				}
			}
		}
		return isIncluded;
	}
	static inline void assign(array *arr, const size_t count, void *data, const size_t index){
		if(arr->dimension > 1 && (*(array**)data)->dimension == arr->dimension){
			printf("Not compatible data.");
			return;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		if(index > arr->size){
			printf("Out of bound.\n");
			return;
		}
		if(index + count >= arr->size){
			size_t moreThanDifference = 0;
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
	static inline void emptyArr(array *arr){
		if(arr->size == 0){
			return;
		}
		removeAt(arr, arr->size - 1, 0);
		arr->size = 0;
	}
	static inline void freeArr(array *arr){
		if(arr->format == 'a'){
			for(size_t i = 0; i < arr->size; i++){
				freeArr(*(array**)at(arr, i));
			}
		}
		else{
			free(arr->arr);
			free(arr->label);
			free(arr);
		}
	}
	static inline int *convertInt(const array *arr){
		if(arr->format != 'i'){
			printf("Wrong data type %c.\n", arr->format);
			return NULL;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		int *a = (int*)malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	static inline double *convertDouble(const array *arr){
		if(arr->format != 'f'){
			printf("Wrong data type %c.\n", arr->format);
			return NULL;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		double *a = (double*)malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	static inline char *convertChar(const array *arr){
		if(arr->format != 'c'){
			printf("Wrong data type %c.\n", arr->format);
			return NULL;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		char *a = (char*)malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	static inline bool *convertBool(const array *arr){
		if(arr->format != 'b'){
			printf("Wrong data type %c.\n", arr->format);
			return NULL;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		bool *a = (bool*)malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	static inline char **convertString(const array *arr){
		if(arr->format != 's'){	
			printf("Wrong data type %c.\n", arr->format);
			return NULL;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		char **a = (char**)malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	static inline array *flatten(array *arr){
		if(arr->dimension == 1){
			array *copy = deepCopyArr(arr);
			return copy;
		}
		else{
			createArr(temp, arr->format, 1, a(arr));
			temp = *((array**)temp->arr);
			createArr(recordOfIndices, 'i', arr->dimension - 1, i());
			fill(recordOfIndices, i(0));
			createArr(finalIndices, 'i', 0, i());
			createArr(indicesCheck, 'b', recordOfIndices->size, b());
			fill(indicesCheck, b(false));
			while(temp->format == 'a'){
				insertEnd(finalIndices, 1, i(temp->size - 1));
				temp = *((array**)at(temp, temp->size - 1));
			}
			createArr(temp1, arr->format, 1, a(arr));
			temp1 = *((array**)temp1->arr);
			const array *temp2 = temp1, *temp3 = temp1;
			int index = 0;
			createArr(temporaryRecord, 'i', 0, i());
			array *flatArrays = NULL;
			switch(temp->format){
				case 'i':{
					createArr(flat, temp->format, 0, i());
					flatArrays = flat;
					break;
				}
				case 'f':{
					createArr(flat, temp->format, 0, f());
					flatArrays = flat;
					break;
				} 
				case 'b':{
					createArr(flat, temp->format, 0, b());
					flatArrays = flat;
					break;
				} 
				case 'c':{
					createArr(flat, temp->format, 0, c());
					flatArrays = flat;
					break;
				}
				case 's':{
					createArr(flat, temp->format, 0, s());
					flatArrays = flat;
					break;
				}
				default:{
					printf("Data type not supported or invalid format = %c.\n", temp->format);
					break;
				}
			}
			bool leaveAfter = false;
			while(true){
				emptyArr(temporaryRecord);
				temp2 = temp1;
				temp3 = temp1;
				while(temp2->dimension >= 1){
					if(temp2->dimension == 1){
						index--;
						if(!leaveAfter){	
							if(temp3->size - 1 == *(int*)at(recordOfIndices, index)){
								assign(recordOfIndices, 1, i(0), recordOfIndices->size - 1);
								assign(recordOfIndices, 1, i(*(int*)at(recordOfIndices, recordOfIndices->size - 2) + 1), recordOfIndices->size - 2);
							}
							else{
								assign(recordOfIndices, 1, i(*(int*)at(recordOfIndices, index) + 1), recordOfIndices->size - 1);
							}
							for(size_t i = 1; i < temporaryRecord->size; i++){
								if(*(int*)at(temporaryRecord, i) == *(int*)at(recordOfIndices, i) - 1){
									size_t elemSize = sizeOfElement(arr->format);
									void *tempIndex = NULL;
									tempIndex = malloc(elemSize);
									if(tempIndex == NULL){
										printf("Memory allocation failed!\n");
										return NULL;
									}
									memcpy(tempIndex, at(recordOfIndices, i - 1), elemSize);
									fill(recordOfIndices, i(0));
									assign(recordOfIndices, 1, i(*(int*)tempIndex + 1), i - 1);
									break;
								}
							}
						}
						for(size_t b = 0; b < temp2->size; b++){
							switch(temp->format){
								case 'i':{
									insertEnd(flatArrays, 1, i(*(int*)at(temp2, b)));
									break;
								}
								case 'f':{
									insertEnd(flatArrays, 1, f(*(double*)at(temp2, b)));
									break;
								}
								case 'b':{
									insertEnd(flatArrays, 1, b(*(bool*)at(temp2, b)));
									break;
								}
								case 'c':{
									insertEnd(flatArrays, 1, c(*(char*)at(temp2, b)));
									break;
								}
								case 's':{
									insertEnd(flatArrays, 1, c(*(char*)at(temp2, b)));
									break;
								}
								default:{
									printf("Data type not supported or invalid format = %c.\n", temp->format);
									break;
								}
							}
						}
						index = 0;
						break;
					}
					else{
						if(temp2->dimension != arr->dimension && temp3->dimension != 1){
							temp3 = *((array**)at(temp3, *(int*)at(recordOfIndices, index)));
						}
						temp2 = *((array**)at(temp2, *(int*)at(recordOfIndices, index)));
						insertEnd(temporaryRecord, 1, i(temp3->size - 1));
						index++;
					}
				}
				if(leaveAfter){
					break;
				}
				for(size_t t = 0; t < finalIndices->size; t++){
					if(*(int*)at(recordOfIndices, t) == *(int*)at(finalIndices, t)){
						assign(indicesCheck, 1, b(true), t);
					}
					else{
						assign(indicesCheck, 1, b(false), t);
					}
				}
				size_t b = 0;
				for(size_t a = 0; a < indicesCheck->size; a++){
					if(*((bool*)at(indicesCheck, a))){
						b++;
					}
				}
				if(b == indicesCheck->size){
					leaveAfter = true;
				}
			}
			return flatArrays;
		}
	}
	#include <sort.h>
#endif
