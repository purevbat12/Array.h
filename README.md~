Generic Array Library


This project aims to produce a generic array behavior seen in many other high level languages. This uses struct to encapsulate metadatas of a created array. It stores many functions and helper functions. With sort.h header it supports sort functions.
 -installation: download the header file and install it into your folder or make it a public variable by putting the file into the include folder of your compiler's directory.
 -All functions and features: {
    i, f, b, c, s, a = these are mandatory macros to be used when your trying to insert, assign or do anything that has to do with manipulating the values of the elements of the array. i = int, f = double, b = bool, c = char, s = string, a = array (multidimensional use)
    createArr = function like macro that creates a new array.
    freeArr = function to free the memory allocated for the array essentially deleting it.
    insertEnd = inserts new elements into the array at the last index.
    insertStart = inserts new elements into the array at the starting index.
    insertAt = inserts new elements into the array at given index.
    removeEnd = removes the elements at the end of the array accordingly to how much elements to be deleted.
    removeStart = removes the elements at the start of the array accordingly to how much elements to be deleted.
    removeAt = removes elements from a given index according to the given amount of elements.
    printArr = prints the array with description and the name given from the start of the initialization of array.
    emptyArr = empties array to 0 element.
    includes = checks whether an array contains an element value given by the user.
    assign = assigns new values to already existing array element index. It can replace as many element the user gives starting from the index the user gives but only within the array's size.
    fill = fills a given array with the same value given by user all over the array within the array's size.
    reverse = reverses the array order.
    at = gives the element of the array according to given index within the array's size
    min/max = returns the max/min element's value's index within a given bound according to the data type.
    sizeOfElement = returns a size value of the data type of the array.
    flatten = flattens a multidimensional array into 1 dimensional array.
    convert(Int, Double, Char, String, Bool) = converts an array with the data type specified in the function's name to an actual array with that data type.
    all Sorting functions = Sorts the arrays in order. Includes: bubble sort, selection sort, insertion sort, binary insertion sort, shaker sort, quick sort, merge sort.
}
Definitions: {
    typedef struct array{
        void *arr;
        size_t size;
        char format;
        char *label;
        size_t dimension;
    } array; => {arr = The array itself, size: The size of the array, format = The format of the data type, label = Label or name of the array stored as a string, dimension = The dimension of the array} 
    createArr(name, form, count, data) => {name: Name of the array. Type without quotation mark, fomr: Format of the data type like 'i', 'f', 'd' and all, count = The amount of inital values the newly created array will have, data = The values that the arrays will have initially. Include only the amounts that is equal to the count parameter. 
    example use{
        createArr(ages, 'i', 5, i(10, 23, 14, 5, 38));
    }
    freeArr(array *arr) => {arr: The array to be freed}
    example use{
        freeArr(ages);
    }
    emptyArr(array*arr) => {arr: The array to be emptied}
    example use{
        emptyArr(ages);
    }
    insertEnd(array *arr, size_t count, void *element) => {arr = Array the element will be inserted into, count = The amount of element that will be added to the array, element = A generic data that can take the forms of (i | f | c | s | b | a)(...) with the elements count being equal to the count parameter}
    exapmle use{
        insertEnd(ages, 3, i(20, 30, 40));
    }
}
