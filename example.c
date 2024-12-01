#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
// #include <time.h>
int FLAG = 1;
const char *SAFE = "SAFE\0";
const char *UNSAFE = "UNSAFE\0";
char output_str[2048];

void vulnerable_put(char *str)
{
    strcat(output_str, str);
}

// Modify printf calls to use vulnerable_put
void UAF_function(void *buffer_1)
{
    memcpy(buffer_1 + 16, UNSAFE, 8);
    memcpy(buffer_1 + 32, UNSAFE, 8);
}

void secret_stack_function()
{
    vulnerable_put("Oops! You are hacked!\n");
    printf("%s\n", output_str);
    exit(0);
}

void vulnerable_stack_function()
{
    uintptr_t secret_addr = (uintptr_t)&secret_stack_function;
    
    vulnerable_put("\n---testing vulnerable_stack_function---\n");
    char buffer[64];
    vulnerable_put("Please do not print anything longer than 64 characters!\n");
    vulnerable_put("Your input: ");
    
    for (int i = 0; i < 64; i++) {
        buffer[i] = 'A';
    }
    memcpy(buffer + 72, &secret_addr, sizeof(secret_addr));
    vulnerable_put(buffer);
}

void vulnerable_heap_function()
{
    vulnerable_put("\n---testing vulnerable_heap_function---\n");
    void *buffer_1 = malloc(8);
    void *buffer_2 = malloc(8);

    memcpy(buffer_2, SAFE, 8);
    free(buffer_1);
    vulnerable_put("SAFE before UAF: ");
    vulnerable_put((char *)buffer_2);
    vulnerable_put("\n");
    if (memcmp(buffer_2, SAFE, 8) != 0)
        printf("ERROR");

    UAF_function(buffer_1);

    vulnerable_put("SAFE after UAF: ");
    vulnerable_put((char *)buffer_2);
    free(buffer_2);
    if (memcmp(buffer_2, UNSAFE, 8) != 0)
        printf("ERROR\n");

    vulnerable_put("\n");
}

void buffer_overflow() {
    // int arr[10];
    // int *ptr = arr;
    // ptr[10] = 10;
    vulnerable_stack_function();
}

void buffer_overflow2() {
    // obtain the address of a pointer
    int *ptr = (int *)malloc(sizeof(int));
    // increase the address of the pointer until buffer overflow
    while (1) {
        printf("Address: %p\n", ptr);
        // read the value of the address
        printf("Value: %d\n", *ptr);
        // increase the pointer by 1024 bytes
        ptr += 1024;
    }
}

void use_after_free() {
    // void *buffer_1 = malloc(8);
    // void *buffer_2 = malloc(8);
    // free(buffer_1);
    // memcpy(buffer_1, UNSAFE, 8);
    // free(buffer_2);
    vulnerable_heap_function();
}

#define SIZE 1024
// #define SIZE 812
int matrixA[SIZE][SIZE], matrixB[SIZE][SIZE], result[SIZE][SIZE];
void performance_test()
{
    // clock_t start = clock();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrixA[i][j] = rand() % 100;
            matrixB[i][j] = rand() % 100;
            result[i][j] = 0;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    // clock_t end = clock();
    // double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Time taken: %f seconds\n", time_taken);

}

int main() {
    // printf("Demonstrating a buffer overflow vulnerability.\n");
    // // buffer_overflow();
    // buffer_overflow2();
    // printf("After buffer overflow.\n");

    // printf("Demonstrating a UAF vulnerability.\n");
    // use_after_free();
    // printf("After UAF.\n");

    printf("Demonstrating a performance issue.\n");
    performance_test();
    

    // // create an arry of 10 integers
    // int arr[10];
    // // get the address of the first element of the array
    // int *ptr = arr;
    // // try to buffer overflow
    // ptr[10] = 10;

    // // keep increase the address of the pointer until buffer overflow
    // while (1) {
    //     printf("Address: %p\n", ptr);
    //     // read the value of the address
    //     printf("Value: %d\n", *ptr);
    //     // increase the pointer by 1024 bytes
    //     ptr += 1024;
    // }

    return 0;
}
