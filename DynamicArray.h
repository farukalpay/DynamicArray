#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>


// DynamicArray structure
typedef struct {
    void* data;
    size_t size;
    size_t capacity;
    size_t element_size;
} DynamicArray;

// Function to initialize a DynamicArray
void initDynamicArray(DynamicArray* array, size_t element_size) {
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
    array->element_size = element_size;
}

// Function to free the memory occupied by a DynamicArray
void freeDynamicArray(DynamicArray* array) {
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}

// Function to push an element to the back of the DynamicArray
void pushBack(DynamicArray* array, const void* value) {
    if (array->size >= array->capacity) {
        size_t new_capacity = array->capacity == 0 ? 1 : array->capacity * 2;
        void* new_data = realloc(array->data, new_capacity * array->element_size);

        if (new_data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        array->data = new_data;
        array->capacity = new_capacity;
    }

    void* destination = (char*)array->data + array->size * array->element_size;
    memcpy(destination, value, array->element_size);

    array->size++;
}

// Function to pop an element from the back of the DynamicArray
void popBack(DynamicArray* array) {
    if (array->size > 0) {
        array->size--;
    }
}

// Function to get the element at a specific index
void* getElementAt(const DynamicArray* array, size_t index) {
    assert(index < array->size); // Check for index out of bounds
    return (char*)array->data + index * array->element_size;
}

// Function to resize the DynamicArray
void resize(DynamicArray* array, size_t new_size) {
    if (new_size < array->size) {
        array->size = new_size;
    }
    else if (new_size > array->size) {
        if (new_size > array->capacity) {
            void* new_data = realloc(array->data, new_size * array->element_size);
            if (new_data == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            array->data = new_data;
            array->capacity = new_size;  // Update capacity to new_size
        }
        array->size = new_size;
    }
}


// Function to concatenate two DynamicArrays
void concatenate(DynamicArray* destination, const DynamicArray* source) {
    size_t new_size = destination->size + source->size;
    if (new_size > destination->capacity) {
        size_t new_capacity = new_size;
        void* new_data = realloc(destination->data, new_capacity * destination->element_size);

        if (new_data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        destination->data = new_data;
        destination->capacity = new_capacity;
    }

    void* destination_ptr = (char*)destination->data + destination->size * destination->element_size;
    const void* source_ptr = source->data;
    size_t bytes_to_copy = source->size * source->element_size;
    memcpy(destination_ptr, source_ptr, bytes_to_copy);

    destination->size = new_size;
}

// Function to clear the DynamicArray
void clearDynamicArray(DynamicArray* array) {
    freeDynamicArray(array);
    initDynamicArray(array, array->element_size);
}