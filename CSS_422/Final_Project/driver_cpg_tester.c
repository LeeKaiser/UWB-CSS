/*
* Improved C program to test heap.c for the midpoint report.
*
* malloc( ): renamed _malloc( )
* free( ): renamed _free( )
* printf( ): included for debugging
* alarm( ): commented out
* signal( ): commented out
*/

#include <string.h> // bzero, strncpy
#include <stdlib.h> // malloc, free
#include <signal.h> // signal
#include <unistd.h> // alarm
#include <stdio.h>  // printf

// External functions implemented in heap.c
extern void *_malloc(int size);  // Custom malloc implementation
extern void *_free(void *ptr);   // Custom free implementation

int *alarmed;  // Pointer for alarm testing (commented out)

void sig_handler1(int signum) {
    *alarmed = 2;
}

void sig_handler2(int signum) {
    *alarmed = 3;
}

int main() {
    printf("=== BEGIN HEAP TEST PROGRAM ===\n\n");

    // Test bzero and strncpy functionality
    char stringA[40] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabc\0";
    char stringB[40];
    bzero(stringB, 40);
    strncpy(stringB, stringA, 40);
    bzero(stringA, 40);

    printf("Initial stringA: \"%s\"\n", stringA);
    printf("Copied stringB: \"%s\"\n\n", stringB);

    // Test memory allocation (_malloc) and deallocation (_free)
    printf("=== MEMORY ALLOCATION TESTS ===\n");

    void *mem1 = _malloc(1024);
    printf("Allocated mem1 (1024 bytes): %p\n", mem1);

    void *mem2 = _malloc(1024);
    printf("Allocated mem2 (1024 bytes): %p\n", mem2);

    void *mem3 = _malloc(8192);
    printf("Allocated mem3 (8192 bytes): %p\n", mem3);

    void *mem4 = _malloc(4096);
    printf("Allocated mem4 (4096 bytes): %p\n", mem4);

    void *mem5 = _malloc(512);
    printf("Allocated mem5 (512 bytes): %p\n", mem5);

    void *mem6 = _malloc(1024);
    printf("Allocated mem6 (1024 bytes): %p\n", mem6);

    void *mem7 = _malloc(512);
    printf("Allocated mem7 (512 bytes): %p\n", mem7);

    // Free some memory blocks
    printf("\n=== MEMORY DEALLOCATION TESTS ===\n");

    _free(mem6);
    printf("Freed mem6 (1024 bytes)\n");

    _free(mem5);
    printf("Freed mem5 (512 bytes)\n");

    _free(mem1);
    printf("Freed mem1 (1024 bytes)\n");

    _free(mem7);
    printf("Freed mem7 (512 bytes)\n");

    _free(mem2);
    printf("Freed mem2 (1024 bytes)\n");

    // Allocate again to test reusability of freed space
    void *mem8 = _malloc(4096);
    printf("\nReallocated mem8 (4096 bytes): %p\n", mem8);

    // Free remaining memory blocks
    _free(mem4);
    printf("Freed mem4 (4096 bytes)\n");

    _free(mem3);
    printf("Freed mem3 (8192 bytes)\n");

    _free(mem8);
    printf("Freed mem8 (4096 bytes)\n");

#if 0
// Uncomment this section to test alarm and signal functionality

    alarmed = (int *)_malloc(4);  // Allocate memory for alarm testing
    *alarmed = 1;
    
    printf("\n=== ALARM AND SIGNAL TESTS ===\n");
    
    printf("Initial alarmed value: %d\n", *alarmed);
    
    signal(SIGALRM, sig_handler1);  // Set signal handler for alarm
    alarm(2);                       // Set alarm for 2 seconds
    
    while (*alarmed != 2) {
        void *mem9 = _malloc(4);   // Allocate small memory blocks in a loop
        _free(mem9);               // Free them immediately
        usleep(1000);              // Small delay to prevent busy-waiting issues
    }
    
    printf("Alarm triggered! Alarmed value: %d\n", *alarmed);

    signal(SIGALRM, sig_handler2);  // Set another signal handler for alarm
    alarm(3);                       // Set alarm for 3 seconds
    
    while (*alarmed != 3) {
        void *mem9 = _malloc(4);   // Allocate small memory blocks in a loop
        _free(mem9);               // Free them immediately
        usleep(1000);              // Small delay to prevent busy-waiting issues
    }
    
    printf("Second alarm triggered! Alarmed value: %d\n", *alarmed);

#endif

    printf("\n=== END HEAP TEST PROGRAM ===\n");
    
    return 0;
}
