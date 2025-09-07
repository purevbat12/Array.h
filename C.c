#include "./include/runtime.h"
#include "./include/sort.h"
#include "./include/array.h"
int main(void){
	cStart(test);
	createArr(testingArr, 'i', 5, i(5, 0, -2, 1, 10));
	printArr(testingArr, "Before sort.");
	bubbleSort(testingArr, "array");
	printArr(testingArr, "After sort.");
	cEnd(test);
	printRuntime(test);
	return 0;
}
