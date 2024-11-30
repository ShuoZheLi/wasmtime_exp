#include <stdio.h>

// void vulnerable_function() {
//     char buffer[2]; // Small buffer

//     printf("Enter a string: ");
//     gets(buffer); // Unsafe function that allows buffer overflow

//     printf("You entered: %s\n", buffer);
// }

int main() {
    printf("Demonstrating a buffer overflow vulnerability.\n");
    // vulnerable_function();

    // create an arry of 10 integers
    int arr[10];
    // get the address of the first element of the array
    int *ptr = arr;
    // try to buffer overflow
    ptr[10] = 10;

    // keep increase the address of the pointer until buffer overflow
    while (1) {
        printf("Address: %p\n", ptr);
        // read the value of the address
        printf("Value: %d\n", *ptr);
        // increase the pointer by 1024 bytes
        ptr += 1024;
        return 0;
    }

    return 0;
}
