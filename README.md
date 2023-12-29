<div align="center">
  
[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/farukalpay/DynamicArray/blob/main/LICENSE)
[![Hits](https://hits.sh/github.com/farukalpay/DynamicArray/tree/main.svg)](https://hits.sh/github.com/farukalpay/DynamicArray/tree/main/)
</div>

## 📝 Documentation
Documentation can be found on the following [link](https://github.com/farukalpay/DynamicArray/blob/main/documentation.pdf)
## ⚙️ Introduction
This library implements a `std::vector` like `Dynamic Array` data structure in C, allowing for the creation, modification, and manipulation of an array whose size can be dynamically adjusted during runtime. Dynamic array is similar to the standard array in C, but it can grow or shrink in size as needed.
## ⚒️ Getting Started
Download the repository and copy the library your local project folder (say, `./myproject`)
```
git clone https://github.com/farukalpay/DynamicArray.git
cp DynamicArray.h ./myproject
```
Import `DynamicArray.h` and get started
```
#include DynamicArray.h
```

###### Example usage is shown below
```c
#include <stdio.h>
#include "DynamicArray.h"

// Structure for a person
typedef struct {
    char name[50];
    int age;
} Person;

int main() {
    DynamicArray personArray;
    initDynamicArray(&personArray, sizeof(Person));

    // Create some Person objects
    Person person1 = { "Alice", 25 };
    Person person2 = { "Bob", 30 };
    Person person3 = { "Charlie", 35 };

    // Push the Person objects into the DynamicArray
    pushBack(&personArray, &person1);
    pushBack(&personArray, &person2);
    pushBack(&personArray, &person3);

    // Get and print the elements in the DynamicArray
    printf("-- Elements Before Update --\n");
    size_t numPersons = personArray.size;
    for (size_t i = 0; i < numPersons; i++) {
        Person* person = (Person*)getElementAt(&personArray, i);
        printf("Name: %s, Age: %d\n", person->name, person->age);
    }

    // Pop an element from the back of the DynamicArray
    popBack(&personArray);

    // Resize the DynamicArray
    resize(&personArray, 2);

    // Create a new DynamicArray
    DynamicArray newPersonArray;
    initDynamicArray(&newPersonArray, sizeof(Person));

    // Create another Person object
    Person person4 = { "David", 40 };

    // Push the Person object into the new DynamicArray
    pushBack(&newPersonArray, &person4);

    // Concatenate the new DynamicArray with the original DynamicArray
    concatenate(&personArray, &newPersonArray);

    // Get and print the updated elements in the DynamicArray
    printf("-- Elements After Update --\n");
    numPersons = personArray.size;
    for (size_t i = 0; i < numPersons; i++) {
        Person* person = (Person*)getElementAt(&personArray, i);
        printf("Name: %s, Age: %d\n", person->name, person->age);
    }

    // Clear the DynamicArray
    clearDynamicArray(&personArray);

    return 0;
}
```
###### Output is shown below
```
-- Elements Before Update --
Name: Alice, Age: 25
Name: Bob, Age: 30
Name: Charlie, Age: 35
-- Elements After Update --
Name: Alice, Age: 25
Name: Bob, Age: 30
Name: David, Age: 40
```

## 🆘 Support
If you find any errors, mistakes please feel free to submit a pull request. If you would like to reach me, you can send me an e-mail via `faruk.1alpayu@gmail.com`
​
