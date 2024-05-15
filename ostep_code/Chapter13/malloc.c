#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    size_t size = 1024 * 1024 * 50;
    printf("My Pid is %d\n", getpid());
    char *large_block = (char *) malloc(size);
    if (large_block == NULL) { 
        perror("Failed to allocate memory"); 
        return EXIT_FAILURE; 
    }
    for (size_t i = 0; i < size; ++i) { large_block[i] = 'A'; }
    while (1) {};
    return EXIT_SUCCESS;
}