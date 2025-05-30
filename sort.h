#ifndef defSort
#define defSort
#include <array.h> 
void BSort(void *arr, char *dataStruct){
	if(!strcmp(dataStruct, "array")){
		array *a = (array*)arr;
		if(a->format == 'b'){
			printf("Cannot sort boolean array.");
			return;
		}
		size_t elemSize = sizeOfElement(a->format);
		for(size_t i = 0; i < a->size; i++){
			for(size_t j = 0; j < a->size - i - 1; j++){
				int swapIndex = max(a, j, j + 1);
				if(swapIndex != -1 || swapIndex != j + 1){
					void *temp = malloc(elemSize);
					if(temp == NULL){
						printf("Memory allocation failed! Exit code 1.\nExiting...");
						exit(1);
					}
					memcpy(temp, at(a, swapIndex), elemSize);
					memcpy(at(a, swapIndex), at(a, j + 1), elemSize);
					memcpy(at(a, j + 1), temp, elemSize);
					free(temp);
				}
			}
		}
	}
}
void SSort(void *arr, char *dataStruct){
	if(!strcmp(dataStruct, "array")){
		array *a = (array*)arr;
		if(a->format == 'b'){
			printf("Cannot sort boolean array.");
			return;
		}
		size_t elemSize = sizeOfElement(a->format);
		void *temp = malloc(elemSize);
		if(temp == NULL){
			printf("Memory allocation failed! Exit code 2.\nExiting...");
			exit(2);
		}
		for(size_t i = 0; i < a->size; i++){
			int minIndex = min(a, i, a->size - 1);
			memcpy(temp, at(a, i), elemSize);
			memcpy(at(a, i), at(a, minIndex), elemSize);
			memcpy(at(a, minIndex), temp, elemSize);
		}
		free(temp);
	}
}
void DSSort(void *arr, char *dataStruct){
	if(!strcmp(dataStruct, "array")){
		array *a = (array*)arr;
		if(a->format == 'b'){
			printf("Cannot sort boolean array.");
			return;
		}
		size_t elemSize = sizeOfElement(a->format);
		void *temp = malloc(elemSize), *temp1 = malloc(elemSize);
		if(temp == NULL || temp1 == NULL){
			printf("Memory allocation failed! Exit code 2.\nExiting...");
			exit(2);
		}
		size_t minIndex = 0, maxIndex = 0;
		for(size_t i = 0; i <= (a->size - 1) / 2; i++){
			int minIndex = min(a, i, a->size - i - 1); 
			memcpy(temp, at(a, i), elemSize);
			memcpy(at(a, i), at(a, minIndex), elemSize);
			memcpy(at(a, minIndex), temp, elemSize);
			int maxIndex = max(a, i, a->size - i - 1);
			memcpy(temp1, at(a, a->size - i - 1), elemSize);
			memcpy(at(a, a->size - i - 1), at(a, maxIndex), elemSize);
			memcpy(at(a, maxIndex), temp1, elemSize);
		}
		free(temp1);
		free(temp);
	}
}
void ISort(void *arr, char *dataStruct){
	if(!strcmp(dataStruct, "array")){
		array *a = (array*)arr;
		if(a->format == 'b'){
			printf("Cannot sort boolean array.");
			return;
		}
		size_t elemSize = sizeOfElement(a->format);
		void *temp = malloc(elemSize);
		if(temp == NULL){
			printf("Memory allocation failed! Exit code 4.\nExiting...");
			exit(4);
		}
		for(size_t i = 1; i < a->size; i++){
			memcpy(temp, at(a, i), elemSize);
			for(size_t j = 0; j < i; j++){
				switch(a->format){
					case 'i':{
						if(*(int*)at(a, i) < *(int*)at(a, j)){
							memmove(at(a, i), at(a, i + 1), (a->size - i - 1) * elemSize);
							memmove(at(a, j + 1), at(a, j), (a->size - j - 1) * elemSize);
							assign(a, 1, temp, j);
						}
					}
				}
			}
		}
	}
}
void BISort(void *arr, char *dataStruct){
	if(!strcmp(dataStruct, "array")){
		array *a = (array*)arr;
		if(a->format == 'b'){
			printf("Cannot sort boolean array.");
			return;
		}
		size_t elemSize = sizeOfElement(a->format);
		void *temp = malloc(elemSize);
		if(temp == NULL){
			printf("Memory allocation failed! Exit code 5.\nExiting...");
			exit(5);
		}
		for(size_t i = 1; i < a->size; i++){
			void *temp1 = at(a, i);
			memcpy(temp, temp1, elemSize); 
			size_t start = 0, end = i, mid = i / 2;
			if(i == 1){
				switch(a->format){
					case 'i':{
						if(*(int*)temp1 < *(int*)at(a, mid)){
							void *temp2 = malloc(elemSize);
							if(temp2 == NULL){
								printf("Memory allocation failed! Exit code 6.\nExiting...");
								exit(6);
							}
							memcpy(temp2, at(a, mid), elemSize);
							memcpy(at(a, mid), temp1, elemSize);
							memcpy(temp1, temp2, elemSize);
						}
					}
				}
			}
			else{
				while(end - start >= 1){
					switch(a->format){
						case 'c':
						case 'i':{
							if(*(int*)temp1 < *(int*)at(a, mid)){
								end = mid; 
							}
							else if(*(int*)temp1 >= *(int*)at(a, mid)){
								start = mid + 1; 
							}
							break;
						}
						case 'f':{
							if(*(double*)temp1 < *(double*)at(a, mid)){
								end = mid; 
							}
							else if(*(double*)temp1 >= *(double*)at(a, mid)){
								start = mid + 1; 
							}
							break;
						}
						case 's':{
							if(strlen(*(char**)temp1) < strlen(*(char**)at(a, mid))){
								end = mid; 
							}
							else if(strlen(*(char**)temp1) >= strlen(*(char**)at(a, mid))){
								start = mid + 1; 
							}
							break;
						}
					}
					mid = (start + end) / 2;
				}
				if(!(end - start >= 1)){
					memmove(temp1, (char*)(a->arr) + (i + 1) * elemSize, (a->size - i - 1) * elemSize);
					memmove((char*)(a->arr) + (mid + 1) * elemSize, (char*)(a->arr) + mid * elemSize, (a->size - mid - 1) * elemSize); 
					memcpy(at(a, mid), temp, elemSize);
				}
			}
		}
		free(temp);	
	}
}
void S1Sort(void *arr, char *dataStruct){
	if(!strcmp(dataStruct, "array")){
		array *a = (array*)arr;
		size_t elemSize = sizeOfElement(a->format);
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
						if(*(int*)at(a, i) > *(int*)at(a, i + 1)){
							swapped = true;
							memcpy(temp, at(a, i), elemSize);
							memcpy(at(a, i), at(a, i + 1), elemSize);
							memcpy(at(a, i + 1), temp, elemSize);
						}
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
						if(*(int*)at(a, i) > *(int*)at(a, i + 1)){
							swapped = true;
							memcpy(temp, at(a, i), elemSize);
							memcpy(at(a, i), at(a, i + 1), elemSize);
							memcpy(at(a, i + 1), temp, elemSize);
						}
					}
				}
			}
		}
	}
}
void QSort(void *arr, char *dataStruct){
	if(!strcmp(dataStruct, "array")){
		array *a = (array*)arr;
		if(a->format == 'b'){
			printf("Cannot sort boolean array.");
			return;
		}
		size_t elemSize = sizeOfElement(a->format);
		if(a->size <= 1){
			return;
		}
		void *pivot = malloc(elemSize); 
		if (pivot == NULL){
			printf("Memory allocation failed! Exit code 7.9.\nExiting...");
			exit(7);
		} 
		memcpy(pivot, at(a, a->size - 1), elemSize);
		int j = 0 - 1;
		for(int i = 0; i < (int)a->size; i++){
			switch(a->format){
				case 'c':
				case 'i':{
					if(*(int*)pivot >= *(int*)at(a, i)){
						j++;
						void *temp = malloc(elemSize);
						if(temp == NULL){
							printf("Memory allocation failed! Exit code 8.\nExiting...");
							exit(8);
						}
						memcpy(temp, at(a, i), elemSize);
						memcpy(at(a, i), at(a, j), elemSize);
						memcpy(at(a, j), temp, elemSize);
						free(temp);
					}
					break;
				}
				case 'f':{
					if(*(double*)pivot >= *(double*)at(a, i)){
						j++;
						void *temp = malloc(elemSize);
						if(temp == NULL){
							printf("Memory allocation failed! Exit code 8.\nExiting...");
							exit(8);
						}
						memcpy(temp, at(a, i), elemSize);
						memcpy(at(a, i), at(a, j), elemSize);
						memcpy(at(a, j), temp, elemSize);
						free(temp);
					}
					break;
				}
				case 's':{
					if(strlen(*(char**)pivot) >= strlen(*(char**)at(a, i))){
						j++;
						void *temp = malloc(elemSize);
						if(temp == NULL){
							printf("Memory allocation failed! Exit code 8.\nExiting...");
							exit(8);
						}
						memcpy(temp, at(a, i), elemSize);
						memcpy(at(a, i), at(a, j), elemSize);
						memcpy(at(a, j), temp, elemSize);
						free(temp);
					}
					break;
				}
			}
		}
		createArr(firstArr, a->format, j, at(a, 0));
		createArr(secondArr, a->format, a->size - j - 1, at(a, j + 1));
		QSort(firstArr, dataStruct);
		QSort(secondArr, dataStruct);
		assign(a, firstArr->size, firstArr->arr, 0);
		assign(a, secondArr->size, secondArr->arr, firstArr->size + 1);
		free(pivot);
		freeArr(firstArr);
		freeArr(secondArr);
	}
}
void MSort(void *arr, char *dataStruct){
	if(!strcmp(dataStruct, "array")){
		array *a = (array*)arr;
		if(a->size <= 1){
			return;
		}
		if(a->format == 'b'){
			printf("Cannot sort boolean array.");
			return;
		}
		size_t elemSize = sizeOfElement(a->format);
		createArr(firstPart, a->format, (a->size / 2) + (a->size % 2 ? 1 : 0), at(a, 0));
		createArr(lastPart, a->format, a->size / 2, at(a, (a->size / 2) + (a->size % 2 ? 1 : 0)));
		MSort(firstPart, "array");
		MSort(lastPart, "array");
		createArr(mergedArr, a->format, a->size, i());
		size_t firstPartIndex = 0, lastPartIndex = 0;
		while(firstPartIndex < firstPart->size || lastPartIndex < lastPart->size){
			switch(a->format){
				case 'c':
				case 'i':{
					if(*(int*)at(firstPart, firstPartIndex) < *(int*)at(lastPart, lastPartIndex)){
						assign(mergedArr, 1, at(firstPart, firstPartIndex), firstPartIndex + lastPartIndex);
						firstPartIndex++;
					}
					else{
						assign(mergedArr, 1, at(lastPart, lastPartIndex), firstPartIndex + lastPartIndex);
						lastPartIndex++;
					}
					break;
				}
				case 'f':{
					if(*(double*)at(firstPart, firstPartIndex) < *(double*)at(lastPart, lastPartIndex)){
						assign(mergedArr, 1, at(firstPart, firstPartIndex), firstPartIndex + lastPartIndex);
						firstPartIndex++;
					}
					else{
						assign(mergedArr, 1, at(lastPart, lastPartIndex), firstPartIndex + lastPartIndex);
						lastPartIndex++;
					}
					break;
				}
				case 's':{
					if(strlen(*(char**)at(firstPart, firstPartIndex)) < strlen(*(char**)at(lastPart, lastPartIndex))){
						assign(mergedArr, 1, at(firstPart, firstPartIndex), firstPartIndex + lastPartIndex);
						firstPartIndex++;
					}
					else{
						assign(mergedArr, 1, at(lastPart, lastPartIndex), firstPartIndex + lastPartIndex);
						lastPartIndex++;
					}
					break;
				}
			}
			if(firstPartIndex >= firstPart->size || lastPartIndex >= lastPart->size){
				if(firstPartIndex >= firstPart->size){
					assign(mergedArr, lastPart->size - lastPartIndex, at(lastPart, lastPartIndex), firstPartIndex + lastPartIndex);
				}
				else if(lastPartIndex >= lastPart->size){
					assign(mergedArr, firstPart->size - firstPartIndex, at(firstPart, firstPartIndex), firstPartIndex + lastPartIndex);
				}
				break;
			}
		}
		assign(a, mergedArr->size, mergedArr->arr, 0);
		freeArr(firstPart);
		freeArr(lastPart);
		freeArr(mergedArr);
	}
}
#endif
