#include "../include/sort.h"
#include "../include/array.h"
	void bubbleSort(void *arr, const char *dataStruct){
		if(!strcmp(dataStruct, "array")){
			const array *a = (array*)arr;
			if(a->format == 'b' || a->format == 'a'){
				printf("Cannot sort boolean array or multi dimensional array.\n");
				return;
			}
			const size_t elemSize = sizeOfElement(a->format);
			for(size_t i = 0; i < a->size; i++){
				for(size_t j = 0; j < a->size - i - 1; j++){
					const int swapIndex = maxArr(a, j, j + 1);
					if(swapIndex != -1 || swapIndex != j + 1){
						void *temp = malloc(elemSize);
						if(temp == NULL){
							printf("Memory allocation failed! Exit code 1.\nExiting...");
							exit(1);
						}
						memcpy(temp, atArr(a, swapIndex), elemSize);
						memcpy(atArr(a, swapIndex), atArr(a, j + 1), elemSize);
						memcpy(atArr(a, j + 1), temp, elemSize);
						free(temp);
					}
				}
			}
		}
	}
	void selectionSort(void *arr, const char *dataStruct){
		if(!strcmp(dataStruct, "array")){
			const array *a = (array*)arr;
			if(a->format == 'b' || a->format == 'a'){
				printf("Cannot sort boolean array or multi dimensional array.\n");
				return;
			}
			const size_t elemSize = sizeOfElement(a->format);
			void *temp = malloc(elemSize);
			if(temp == NULL){
				printf("Memory allocation failed! Exit code 2.\nExiting...");
				exit(2);
			}
			for(size_t i = 0; i < a->size; i++){
				const int minIndex = minArr(a, i, a->size - 1);
				memcpy(temp, atArr(a, i), elemSize);
				memcpy(atArr(a, i), atArr(a, minIndex), elemSize);
				memcpy(atArr(a, minIndex), temp, elemSize);
			}
			free(temp);
		}
	}
	void doubleSelectionSort(void *arr, const char *dataStruct){
		if(!strcmp(dataStruct, "array")){
			const array *a = (array*)arr;
			if(a->format == 'b' || a->format == 'a'){
				printf("Cannot sort boolean array or multi dimensional array.\n");
				return;
			}
			const size_t elemSize = sizeOfElement(a->format);
			void *temp = malloc(elemSize), *temp1 = malloc(elemSize);
			if(temp == NULL || temp1 == NULL){
				printf("Memory allocation failed! Exit code 2.\nExiting...");
				exit(2);
			}
			size_t minIndex = 0, maxIndex = 0;
			for(size_t i = 0; i <= (a->size - 1) / 2; i++){
				const int minIndex = minArr(a, i, a->size - i - 1);
				memcpy(temp, atArr(a, i), elemSize);
				memcpy(atArr(a, i), atArr(a, minIndex), elemSize);
				memcpy(atArr(a, minIndex), temp, elemSize);
				const int maxIndex = maxArr(a, i, a->size - i - 1);
				memcpy(temp1, atArr(a, a->size - i - 1), elemSize);
				memcpy(atArr(a, a->size - i - 1), atArr(a, maxIndex), elemSize);
				memcpy(atArr(a, maxIndex), temp1, elemSize);
			}
			free(temp1);
			free(temp);
		}
	}
	void insertionSort(void *arr, const char *dataStruct){
		if(!strcmp(dataStruct, "array")){
			array *a = (array*)arr;
			if(a->format == 'b' || a->format == 'a'){
				printf("Cannot sort boolean array or multi dimensional array.\n");
				return;
			}
			const size_t elemSize = sizeOfElement(a->format);
			void *temp = malloc(elemSize);
			if(temp == NULL){
				printf("Memory allocation failed! Exit code 4.\nExiting...");
				exit(4);
			}
			for(size_t i = 1; i < a->size; i++){
				memcpy(temp, atArr(a, i), elemSize);
				for(size_t j = 0; j < i; j++){
					switch(a->format){
						case 'i':{
							if(*(int*)atArr(a, i) < *(int*)atArr(a, j)){
								memmove(atArr(a, i), atArr(a, i + 1), (a->size - i - 1) * elemSize);
								memmove(atArr(a, j + 1), atArr(a, j), (a->size - j - 1) * elemSize);
								assignArr(a, 1, temp, j);
							}
							break;
						}
						case 'f':{
							if(*(double*)atArr(a, i) < *(double*)atArr(a, j)){
								memmove(atArr(a, i), atArr(a, i + 1), (a->size - i - 1) * elemSize);
								memmove(atArr(a, j + 1), atArr(a, j), (a->size - j - 1) * elemSize);
								assignArr(a, 1, temp, j);
							}
							break;
						}
						case 'c':{
							if(*(char*)atArr(a, i) < *(char*)atArr(a, j)){
								memmove(atArr(a, i), atArr(a, i + 1), (a->size - i - 1) * elemSize);
								memmove(atArr(a, j + 1), atArr(a, j), (a->size - j - 1) * elemSize);
								assignArr(a, 1, temp, j);
							}
							break;
						}
						case 's':{
							if(strlen(*(char**)atArr(a, i)) < strlen(*(char**)atArr(a, j))){
								memmove(atArr(a, i), atArr(a, i + 1), (a->size - i - 1) * elemSize);
								memmove(atArr(a, j + 1), atArr(a, j), (a->size - j - 1) * elemSize);
								assignArr(a, 1, temp, j);
							}
							break;
						}
						default: {
							printf("Not supported data type!");
						}
					}
				}
			}
		}
	}
	void binaryInsertionSort(void *arr, const char *dataStruct){
		if(!strcmp(dataStruct, "array")){
			const array *a = (array*)arr;
			if(a->format == 'b' || a->format == 'a'){
				printf("Cannot sort boolean array or multi dimensional array.\n");
				return;
			}
			const size_t elemSize = sizeOfElement(a->format);
			void *temp = malloc(elemSize);
			if(temp == NULL){
				printf("Memory allocation failed! Exit code 5.\nExiting...");
				exit(5);
			}
			for(size_t i = 1; i < a->size; i++){
				void *temp1 = atArr(a, i);
				memcpy(temp, temp1, elemSize);
				size_t start = 0, end = i, mid = i / 2;
				if(i == 1){
					switch(a->format){
						case 'i':{
							if(*(int*)temp1 < *(int*)atArr(a, mid)){
								void *temp2 = malloc(elemSize);
								if(temp2 == NULL){
									printf("Memory allocation failed! Exit code 6.\nExiting...");
									exit(6);
								}
								memcpy(temp2, atArr(a, mid), elemSize);
								memcpy(atArr(a, mid), temp1, elemSize);
								memcpy(temp1, temp2, elemSize);
								free(temp2);
							}
							break;
						}
						case 'f':{
							if(*(double*)temp1 < *(double*)atArr(a, mid)){
								void *temp2 = malloc(elemSize);
								if(temp2 == NULL){
									printf("Memory allocation failed! Exit code 6.\nExiting...");
									exit(6);
								}
								memcpy(temp2, atArr(a, mid), elemSize);
								memcpy(atArr(a, mid), temp1, elemSize);
								memcpy(temp1, temp2, elemSize);
								free(temp2);
							}
							break;
						}
						case 'c':{
							if(*(char*)temp1 < *(char*)atArr(a, mid)){
								void *temp2 = malloc(elemSize);
								if(temp2 == NULL){
									printf("Memory allocation failed! Exit code 6.\nExiting...");
									exit(6);
								}
								memcpy(temp2, atArr(a, mid), elemSize);
								memcpy(atArr(a, mid), temp1, elemSize);
								memcpy(temp1, temp2, elemSize);
								free(temp2);
							}
							break;
						}
						case 's':{
							if(strlen(*(char**)temp1) < strlen(*(char**)atArr(a, mid))){
								void *temp2 = malloc(elemSize);
								if(temp2 == NULL){
									printf("Memory allocation failed! Exit code 6.\nExiting...");
									exit(6);
								}
								memcpy(temp2, atArr(a, mid), elemSize);
								memcpy(atArr(a, mid), temp1, elemSize);
								memcpy(temp1, temp2, elemSize);
								free(temp2);
							}
							break;
						}
						default: {
							printf("Not supported data type!");
						}
					}
				}
				else{
					while(end - start >= 1){
						switch(a->format){
							case 'c':
							case 'i':{
								if(*(int*)temp1 < *(int*)atArr(a, mid)){
									end = mid;
								}
								else if(*(int*)temp1 >= *(int*)atArr(a, mid)){
									start = mid + 1;
								}
								break;
							}
							case 'f':{
								if(*(double*)temp1 < *(double*)atArr(a, mid)){
									end = mid;
								}
								else if(*(double*)temp1 >= *(double*)atArr(a, mid)){
									start = mid + 1;
								}
								break;
							}
							case 's':{
								if(strlen(*(char**)temp1) < strlen(*(char**)atArr(a, mid))){
									end = mid;
								}
								else if(strlen(*(char**)temp1) >= strlen(*(char**)atArr(a, mid))){
									start = mid + 1;
								}
								break;
							}
							default: {
								printf("Not supported data type!");
							}
						}
						mid = (start + end) / 2;
					}
					if(!(end - start >= 1)){
						memmove(temp1, (char*)(a->arr) + (i + 1) * elemSize, (a->size - i - 1) * elemSize);
						memmove((char*)(a->arr) + (mid + 1) * elemSize, (char*)(a->arr) + mid * elemSize, (a->size - mid - 1) * elemSize);
						memcpy(atArr(a, mid), temp, elemSize);
					}
				}
			}
			free(temp);
		}
	}
	void shakerSort(void *arr, const char *dataStruct){
		if(!strcmp(dataStruct, "array")){
			const array *a = (array*)arr;
			if(a->format == 'b' || a->format == 'a'){
				printf("Cannot sort boolean array or multi dimensional array.\n");
				return;
			}
			const size_t elemSize = sizeOfElement(a->format);
			void *temp= malloc(elemSize);
			if(temp == NULL){
				printf("Memory allocation failed! Exit code 7.\nExiting...");
				exit(7);
			}
			bool swapped = true;
			while(swapped){
				swapped = false;
				for(int i = 0; i < (int)(a->size) - 1; i++){
					switch(a->format){
						case 'i':{
							if(*(int*)atArr(a, i) > *(int*)atArr(a, i + 1)){
								swapped = true;
								memcpy(temp, atArr(a, i), elemSize);
								memcpy(atArr(a, i), atArr(a, i + 1), elemSize);
								memcpy(atArr(a, i + 1), temp, elemSize);
							}
							break;
						}
						case 'f':{
							if(*(double*)atArr(a, i) > *(double*)atArr(a, i + 1)){
								swapped = true;
								memcpy(temp, atArr(a, i), elemSize);
								memcpy(atArr(a, i), atArr(a, i + 1), elemSize);
								memcpy(atArr(a, i + 1), temp, elemSize);
							}
							break;
						}
						case 'c':{
							if(*(char*)atArr(a, i) > *(char*)atArr(a, i + 1)){
								swapped = true;
								memcpy(temp, atArr(a, i), elemSize);
								memcpy(atArr(a, i), atArr(a, i + 1), elemSize);
								memcpy(atArr(a, i + 1), temp, elemSize);
							}
							break;
						}
						case 's':{
							if(strlen(*(char**)atArr(a, i)) > strlen(*(char**)atArr(a, i + 1))){
								swapped = true;
								memcpy(temp, atArr(a, i), elemSize);
								memcpy(atArr(a, i), atArr(a, i + 1), elemSize);
								memcpy(atArr(a, i + 1), temp, elemSize);
							}
							break;
						}
						default: {
							printf("Not supported data type!");
						}
					}
				}
				if(!swapped){
					break;
				}
				swapped = false;
				for(int i = (int)(a->size) - 2; i >= 0; i--){
					switch(a->format){
						case 'i':{
							if(*(int*)atArr(a, i) > *(int*)atArr(a, i + 1)){
								swapped = true;
								memcpy(temp, atArr(a, i), elemSize);
								memcpy(atArr(a, i), atArr(a, i + 1), elemSize);
								memcpy(atArr(a, i + 1), temp, elemSize);
							}
							break;
						}
						case 'f':{
							if(*(double*)atArr(a, i) > *(double*)atArr(a, i + 1)){
								swapped = true;
								memcpy(temp, atArr(a, i), elemSize);
								memcpy(atArr(a, i), atArr(a, i + 1), elemSize);
								memcpy(atArr(a, i + 1), temp, elemSize);
							}
							break;
						}
						case 'c':{
							if(*(char*)atArr(a, i) > *(char*)atArr(a, i + 1)){
								swapped = true;
								memcpy(temp, atArr(a, i), elemSize);
								memcpy(atArr(a, i), atArr(a, i + 1), elemSize);
								memcpy(atArr(a, i + 1), temp, elemSize);
							}
							break;
						}
						case 's':{
							if(strlen(*(char**)atArr(a, i)) > strlen(*(char**)atArr(a, i + 1))){
								swapped = true;
								memcpy(temp, atArr(a, i), elemSize);
								memcpy(atArr(a, i), atArr(a, i + 1), elemSize);
								memcpy(atArr(a, i + 1), temp, elemSize);
							}
							break;
						}
						default: {
							printf("Not supported data type!");
						}
					}
				}
			}
			free(temp);
		}
	}
	void quickSort(void *arr, const char *dataStruct){
		if(!strcmp(dataStruct, "array")){
			array *a = (array*)arr;
			if(a->format == 'b' || a->format == 'a'){
				printf("Cannot sort boolean array or multi dimensional array.\n");
				return;
			}
			const size_t elemSize = sizeOfElement(a->format);
			if(a->size <= 1){
				return;
			}
			void *pivot = malloc(elemSize);
			if (pivot == NULL){
				printf("Memory allocation failed! Exit code 7.9.\nExiting...");
				exit(7);
			}
			memcpy(pivot, atArr(a, a->size - 1), elemSize);
			int j = 0 - 1;
			for(int i = 0; i < (int)a->size; i++){
				switch(a->format){
					case 'c':
					case 'i':{
						if(*(int*)pivot >= *(int*)atArr(a, i)){
							j++;
							void *temp = malloc(elemSize);
							if(temp == NULL){
								printf("Memory allocation failed! Exit code 8.\nExiting...");
								exit(8);
							}
							memcpy(temp, atArr(a, i), elemSize);
							memcpy(atArr(a, i), atArr(a, j), elemSize);
							memcpy(atArr(a, j), temp, elemSize);
							free(temp);
						}
						break;
					}
					case 'f':{
						if(*(double*)pivot >= *(double*)atArr(a, i)){
							j++;
							void *temp = malloc(elemSize);
							if(temp == NULL){
								printf("Memory allocation failed! Exit code 8.\nExiting...");
								exit(8);
							}
							memcpy(temp, atArr(a, i), elemSize);
							memcpy(atArr(a, i), atArr(a, j), elemSize);
							memcpy(atArr(a, j), temp, elemSize);
							free(temp);
						}
						break;
					}
					case 's':{
						if(strlen(*(char**)pivot) >= strlen(*(char**)atArr(a, i))){
							j++;
							void *temp = malloc(elemSize);
							if(temp == NULL){
								printf("Memory allocation failed! Exit code 8.\nExiting...");
								exit(8);
							}
							memcpy(temp, atArr(a, i), elemSize);
							memcpy(atArr(a, i), atArr(a, j), elemSize);
							memcpy(atArr(a, j), temp, elemSize);
							free(temp);
						}
						break;
					}
					default: {
						printf("Not supported data type!");
					}
				}
			}
			createArr(firstArr, a->format, j, atArr(a, 0));
			createArr(secondArr, a->format, a->size - j - 1, atArr(a, j + 1));
			quickSort(firstArr, dataStruct);
			quickSort(secondArr, dataStruct);
			assignArr(a, firstArr->size, firstArr->arr, 0);
			assignArr(a, secondArr->size, secondArr->arr, firstArr->size + 1);
			free(pivot);
			freeArr(firstArr);
			freeArr(secondArr);
		}
	}
	void mergeSort(void *arr, const char *dataStruct){
		if(!strcmp(dataStruct, "array")){
			array *a = (array*)arr;
			if(a->size <= 1){
				return;
			}
			if(a->format == 'b' || a->format == 'a'){
				printf("Cannot sort boolean array or multi dimensional array.\n");
				return;
			}
			size_t elemSize = sizeOfElement(a->format);
			createArr(firstPart, a->format, (a->size / 2) + (a->size % 2 ? 1 : 0), atArr(a, 0));
			createArr(lastPart, a->format, a->size / 2, atArr(a, (a->size / 2) + (a->size % 2 ? 1 : 0)));
			mergeSort(firstPart, "array");
			mergeSort(lastPart, "array");
			createArr(mergedArr, a->format, a->size, i());
			size_t firstPartIndex = 0, lastPartIndex = 0;
			while(firstPartIndex < firstPart->size || lastPartIndex < lastPart->size){
				switch(a->format){
					case 'c':
					case 'i':{
						if(*(int*)atArr(firstPart, firstPartIndex) < *(int*)atArr(lastPart, lastPartIndex)){
							assignArr(mergedArr, 1, atArr(firstPart, firstPartIndex), firstPartIndex + lastPartIndex);
							firstPartIndex++;
						}
						else{
							assignArr(mergedArr, 1, atArr(lastPart, lastPartIndex), firstPartIndex + lastPartIndex);
							lastPartIndex++;
						}
						break;
					}
					case 'f':{
						if(*(double*)atArr(firstPart, firstPartIndex) < *(double*)atArr(lastPart, lastPartIndex)){
							assignArr(mergedArr, 1, atArr(firstPart, firstPartIndex), firstPartIndex + lastPartIndex);
							firstPartIndex++;
						}
						else{
							assignArr(mergedArr, 1, atArr(lastPart, lastPartIndex), firstPartIndex + lastPartIndex);
							lastPartIndex++;
						}
						break;
					}
					case 's':{
						if(strlen(*(char**)atArr(firstPart, firstPartIndex)) < strlen(*(char**)atArr(lastPart, lastPartIndex))){
							assignArr(mergedArr, 1, atArr(firstPart, firstPartIndex), firstPartIndex + lastPartIndex);
							firstPartIndex++;
						}
						else{
							assignArr(mergedArr, 1, atArr(lastPart, lastPartIndex), firstPartIndex + lastPartIndex);
							lastPartIndex++;
						}
						break;
					}
					default: {
						printf("Not supported data type!");
					}
				}
				if(firstPartIndex >= firstPart->size || lastPartIndex >= lastPart->size){
					if(firstPartIndex >= firstPart->size){
						assignArr(mergedArr, lastPart->size - lastPartIndex, atArr(lastPart, lastPartIndex), firstPartIndex + lastPartIndex);
					}
					else if(lastPartIndex >= lastPart->size){
						assignArr(mergedArr, firstPart->size - firstPartIndex, atArr(firstPart, firstPartIndex), firstPartIndex + lastPartIndex);
					}
					break;
				}
			}
			assignArr(a, mergedArr->size, mergedArr->arr, 0);
			freeArr(firstPart);
			freeArr(lastPart);
			freeArr(mergedArr);
		}
	}
