#include <stdlib.h>
#include <stdio.h>

int main()
{  
   
    printf("Back in main, program will now exit normally.\n");

    int *ptr = (int *)malloc(sizeof(int)); // Allocate memory
    *ptr = 42;                            // Use the memory
    free(ptr);                            // Free the memory


    // wasmtime: didn't catch this UAF
    // wmemcheck: caught this UAF
    printf("%d\n", *ptr); // UAF: Accessing freed memory

    return 0;
}