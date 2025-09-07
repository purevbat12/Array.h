#include "../include/array.h"
	size_t sizeOfElement(const char format){
		return format == 'i' ? intArr : (format == 'f') ? doubleArr : (format == 'b') ? boolArr : (format == 'c') ? string :  (format == 's') ? stringArr : (format == 'a') ? sizeof(array*) : 0;
	}
	size_t minArr(const array *arr, const size_t start, const size_t end){
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
					if(*(int*)atArr(arr, i) < *(int*)atArr(arr, result)){
						result = i;
					}
					break;
				}
				case 'f':{
					if(*(double*)atArr(arr, i) < *(double*)atArr(arr, result)){
						result = i;
					}
					break;
				}
				case 's':{
					if(strlen(*(char**)atArr(arr, i)) > strlen(*(char**)atArr(arr, result))){
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
	size_t maxArr(const array *arr, const size_t start, const size_t end){
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
					if(*(int*)atArr(arr, i) > *(int*)atArr(arr, result)){
						result = i;
					}
					break;
				}
				case 'f':{
					if(*(double*)atArr(arr, i) > *(double*)atArr(arr, result)){
						result = i;
					}
					break;
				}
				case 's':{
					if(strlen(*(char**)atArr(arr, i)) > strlen(*(char**)atArr(arr, result))){
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
	void *atArr(const array *arr, const size_t index){
		const size_t elemSize = sizeOfElement(arr->format);
		if(index > arr->size && arr->size > 0){
			printf("Out of bound in at func.\n");
			return NULL;
		}
		return (char*)(arr->arr) + elemSize * index;
	}
	void printArr(const array *arr, char *desc){
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
					printf("%d ", *((int*)(atArr(arr, i))));
					break;
				}
				case 'f':{
					printf("%.2f ", *((double*)(atArr(arr, i))));
					break;
				}
				case 'c':{
					printf("%c ", *((char*)(atArr(arr, i))));
					break;
				}
				case 'b':{
					printf("%s ", *((int*)(atArr(arr, i))) ? "true" : "false");
					break;
				}
				case 's':{
					printf("\"%s\" ", *(char**)atArr(arr, i));
					break;
				}
				case 'a':{
					const array *temp = arr;
					printArr(*((array**)atArr(temp, i)), "R");
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
	void removeAtArr(array *arr, const size_t count, size_t index){
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
			memmove(atArr(arr, i), atArr(arr, i + count), elemSize);
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
	void removeEndArr(array *arr, const size_t count){
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
	void removeStartArr(array *arr, const size_t count){
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
			memcpy(atArr(arr, i), atArr(arr, i + count), elemSize);
		}
		arr->arr = realloc(arr->arr, elemSize * (arr->size - count));
		if(arr->arr == NULL && count != arr->size){
			printf("Memory allocation failed! Exit code 8.\nExiting...");
			exit(8);
		}
		arr->size -= count;
	}
	array *deepCopyArr(const array *data){
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
	void insertEndArr(array *arr, const size_t count, void *data){
		insertAtArr(arr, count, data, arr->size - 1);
	}
	void insertStartArr(array *arr, const size_t count, void *data){
		insertAtArr(arr, count, data, 0);
	}
	void insertAtArr(array *arr, const size_t count, void *data, const size_t index){
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
	void fillArr(const array *arr, void *data){
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
			memcpy(atArr(arr, i), data, elemSize);
		}
	}
	void reverseArr(array *arr){
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
			memcpy(temp, atArr(arr, i), elemSize);
			assignArr(arr, 1, atArr(arr, arr->size - i - 1), i);
			assignArr(arr, 1, temp, arr->size - i - 1);
		}
	}
	bool includesArr(const array *arr, void *data){
		if(arr->size == 0){
			printf("An empty array.\n");
			return false;
		}
		bool isIncluded = false;
		for(size_t i = 0; i < arr->size; i++){
			switch(arr->format){
				case 'i':{
					if(*((int*)(data)) == *((int*)atArr(arr, i))){
						isIncluded = true;
					}
					break;
				}
				case 'f':{
					if(*((double*)(data)) == *((double*)atArr(arr, i))){
						isIncluded = true;
					}
					break;
				}
				case 'b':{
					if(*((bool*)(data)) == *((bool*)atArr(arr, i))){
						isIncluded = true;
					}
					break;
				}
				case 'c':{
					if(*((char*)(data)) == *((char*)atArr(arr, i))){
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
					if(*(array**)data == *(array**)atArr(arr, i)){
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
	void assignArr(array *arr, const size_t count, void *data, const size_t index){
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
		memcpy(atArr(arr, index), data, elemSize * count);
	}
	void emptyArr(array *arr){
		if(arr->size == 0){
			return;
		}
		removeAtArr(arr, arr->size - 1, 0);
		arr->size = 0;
	}
	void freeArr(array *arr){
		if(arr->format == 'a'){
			for(size_t i = 0; i < arr->size; i++){
				freeArr(*(array**)atArr(arr, i));
			}
		}
		else{
			free(arr->arr);
			free(arr->label);
			free(arr);
		}
	}
	int *convertIntArr(const array *arr){
		if(arr->format != 'i'){
			printf("Wrong data type %c.\n", arr->format);
			return NULL;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		const auto a = (int*)malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	double *convertDoubleArr(const array *arr){
		if(arr->format != 'f'){
			printf("Wrong data type %c.\n", arr->format);
			return NULL;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		const auto a = (double*)malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	char *convertCharArr(const array *arr){
		if(arr->format != 'c'){
			printf("Wrong data type %c.\n", arr->format);
			return NULL;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		const auto a = (char*)malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	bool *convertBoolArr(const array *arr){
		if(arr->format != 'b'){
			printf("Wrong data type %c.\n", arr->format);
			return NULL;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		const auto a = (bool*)malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	char **convertStringArr(const array *arr){
		if(arr->format != 's'){
			printf("Wrong data type %c.\n", arr->format);
			return NULL;
		}
		const size_t elemSize = sizeOfElement(arr->format);
		const auto a = (char**)malloc(arr->size * elemSize);
		if(a == NULL){
			printf("Memory allocation failed!\n Exit code 100.\nExiting...");
			exit(100);
		}
		memcpy(a, arr->arr, arr->size * elemSize);
		return a;
	}
	array *flattenArr(array *arr){
		if(arr->dimension == 1){
			array *copy = deepCopyArr(arr);
			return copy;
		}
		else{
			createArr(temp, arr->format, 1, a(arr));
			temp = *((array**)temp->arr);
			createArr(recordOfIndices, 'i', arr->dimension - 1, i());
			fillArr(recordOfIndices, i(0));
			createArr(finalIndices, 'i', 0, i());
			createArr(indicesCheck, 'b', recordOfIndices->size, b());
			fillArr(indicesCheck, b(false));
			while(temp->format == 'a'){
				insertEndArr(finalIndices, 1, i(temp->size - 1));
				temp = *((array**)atArr(temp, temp->size - 1));
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
							if(temp3->size - 1 == *(int*)atArr(recordOfIndices, index)){
								assignArr(recordOfIndices, 1, i(0), recordOfIndices->size - 1);
								assignArr(recordOfIndices, 1, i(*(int*)atArr(recordOfIndices, recordOfIndices->size - 2) + 1), recordOfIndices->size - 2);
							}
							else{
								assignArr(recordOfIndices, 1, i(*(int*)atArr(recordOfIndices, index) + 1), recordOfIndices->size - 1);
							}
							for(size_t i = 1; i < temporaryRecord->size; i++){
								if(*(int*)atArr(temporaryRecord, i) == *(int*)atArr(recordOfIndices, i) - 1){
									size_t elemSize = sizeOfElement(arr->format);
									auto tempIndex = NULL;
									tempIndex = malloc(elemSize);
									if(tempIndex == NULL){
										printf("Memory allocation failed!\n");
										return NULL;
									}
									memcpy(tempIndex, atArr(recordOfIndices, i - 1), elemSize);
									fillArr(recordOfIndices, i(0));
									assignArr(recordOfIndices, 1, i(*(int*)tempIndex + 1), i - 1);
									break;
								}
							}
						}
						for(size_t b = 0; b < temp2->size; b++){
							switch(temp->format){
								case 'i':{
									insertEndArr(flatArrays, 1, i(*(int*)atArr(temp2, b)));
									break;
								}
								case 'f':{
									insertEndArr(flatArrays, 1, f(*(double*)atArr(temp2, b)));
									break;
								}
								case 'b':{
									insertEndArr(flatArrays, 1, b(*(bool*)atArr(temp2, b)));
									break;
								}
								case 'c':{
									insertEndArr(flatArrays, 1, c(*(char*)atArr(temp2, b)));
									break;
								}
								case 's':{
									insertEndArr(flatArrays, 1, c(*(char*)atArr(temp2, b)));
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
							temp3 = *((array**)atArr(temp3, *(int*)atArr(recordOfIndices, index)));
						}
						temp2 = *((array**)atArr(temp2, *(int*)atArr(recordOfIndices, index)));
						insertEndArr(temporaryRecord, 1, i(temp3->size - 1));
						index++;
					}
				}
				if(leaveAfter){
					break;
				}
				for(size_t t = 0; t < finalIndices->size; t++){
					if(*(int*)atArr(recordOfIndices, t) == *(int*)atArr(finalIndices, t)){
						assignArr(indicesCheck, 1, b(true), t);
					}
					else{
						assignArr(indicesCheck, 1, b(false), t);
					}
				}
				size_t b = 0;
				for(size_t a = 0; a < indicesCheck->size; a++){
					if(*((bool*)atArr(indicesCheck, a))){
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
