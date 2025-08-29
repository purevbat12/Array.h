#include <array.h> 
#include <stdio.h>
#include <runtime.h>
int main(void){
	cStart(runtime);
	createArr(arr2, 'i', 5, i(4, 1, 55, 21, 5));
	createArr(arr1, 'c', 6, c('a', 'c', 'b', 'f', 'e', 'h')); 
	createArr(strArr, 's', 3, s("Hello", "is", "apple"));
	printArr(arr2, "");
	quickSort(arr2);
	printArr(arr2, "Quick Sorted arr2.");
	printArr(arr1, ""); 
	bubbleSort(arr1);
	printArr(arr1, "Bubble Sorted arr1."); 
	printArr(strArr, ""); 
	mergeSort(strArr);
	printArr(strArr, "Merge Sorted strArr.");
	char **stringArray = convertString(strArr);
	printf("stringArray = {");
	for(size_t i = 0; i < strArr->size; i++){
		printf("%s ", stringArray[i]);
	}
	printf("}\n");
	freeArr(arr1);
	freeArr(arr2);
	cEnd(runtime);
	printRuntime(runtime);
	return 0;
}
