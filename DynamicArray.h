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

// Function to clear the DynamicArray
void clearDynamicArray(DynamicArray* array) {
    freeDynamicArray(array);
    initDynamicArray(array, array->element_size);
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

// Function to trim the capacity of the DynamicArray to match its size
void trimToSize(DynamicArray* array) {
    if (array->size < array->capacity) {
        size_t new_capacity = array->size;
        void* new_data = realloc(array->data, new_capacity * array->element_size);

        if (new_data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        array->data = new_data;
        array->capacity = new_capacity;
    }
}


// Function to pop an element from the back of the DynamicArray
void popBack(DynamicArray* array) {
    if (array->size > 0) {
        array->size--;
        trimToSize(array);
    }
}

// Function to delete an element at a specific index
void deleteAt(DynamicArray* array, size_t index) {
    assert(index < array->size);

    // Shift elements to fill the gap left by the deleted one
    void* delete_location = (char*)array->data + index * array->element_size;
    size_t bytes_to_shift = (array->size - index - 1) * array->element_size;
    memmove(delete_location, (char*)delete_location + array->element_size, bytes_to_shift);

    trimToSize(array);
    array->size--;
}

// Function to get the element at a specific index
void* getElementAt(const DynamicArray* array, size_t index) {
    assert(index < array->size); // Check for index out of bounds
    return (char*)array->data + index * array->element_size;
}

// Function to find an element in the array
size_t findElement(const DynamicArray* array, const void* value) {
    for (size_t i = 0; i < array->size; ++i) {
        void* current_element = getElementAt(array, i);
        if (memcmp(current_element, value, array->element_size) == 0) {
            return i; // Found the element at index i
        }
    }
    return SIZE_MAX; // Element not found
}

// Function to erase the first occurrence of an element from the array
void eraseElement(DynamicArray* array, const void* value) {
    size_t index = findElement(array, value);
    if (index != SIZE_MAX) {
        deleteAt(array, index);
    }
}

// Function to insert an element at a specific index
void insertAt(DynamicArray* array, size_t index, const void* value) {
    assert(index <= array->size);

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

    // Shift elements to make room for the new one
    void* insert_location = (char*)array->data + index * array->element_size;
    size_t bytes_to_shift = (array->size - index) * array->element_size;
    memmove((char*)insert_location + array->element_size, insert_location, bytes_to_shift);

    // Copy the new element to the insert location
    memcpy(insert_location, value, array->element_size);

    array->size++;
}

// Function to Reserve Capacity in a DynamicArray
void reserve(DynamicArray* array, size_t new_capacity) {
    if (new_capacity > array->capacity) {
        void* new_data = realloc(array->data, new_capacity * array->element_size);

        if (new_data == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(EXIT_FAILURE);
        }

        array->data = new_data;
        array->capacity = new_capacity;
    }
}

// Function to Resize a DynamicArray
void resize(DynamicArray* array, size_t new_size) {
    if (new_size < array->size) {
        array->size = new_size;
        trimToSize(array);
    }
    else if (new_size > array->size) {
        reserve(array, new_size); // This will also handle potential shrinking
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
