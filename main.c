#include <stdio.h>
#include "DynamicArray.h"

int main() {
    // Example with integers
    DynamicArray intArray;
    initDynamicArray(&intArray, sizeof(int));

    int values[] = { 1, 2, 3, 4, 5 };
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        pushBack(&intArray, &values[i]);
    }

    printf("Integer Array (Size: %zu): ", intArray.size);
    for (size_t i = 0; i < intArray.size; ++i) {
        int* element = (int*)getElementAt(&intArray, i);
        printf("%d ", *element);
    }
    printf("\n");

    // Example with characters
    DynamicArray charArray;
    initDynamicArray(&charArray, sizeof(char));

    char chars[] = { 'A', 'B', 'C', 'D', 'E' };
    for (size_t i = 0; i < sizeof(chars) / sizeof(chars[0]); ++i) {
        pushBack(&charArray, &chars[i]);
    }

    printf("Character Array (Size: %zu): ", charArray.size);
    for (size_t i = 0; i < charArray.size; ++i) {
        char* element = (char*)getElementAt(&charArray, i);
        printf("%c ", *element);
    }
    printf("\n");

    // Clean up
    freeDynamicArray(&intArray);
    printf("Integer Array Size after cleanup: %zu\n", intArray.size);

    freeDynamicArray(&charArray);
    printf("Character Array Size after cleanup: %zu\n", charArray.size);

    return 0;
}