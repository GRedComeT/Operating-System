#include <stdio.h>
#include <unistd.h>

extern char** environ;

int main(int argc, char* argv[]) {
    for (char* *ptr = environ; *ptr != NULL; ptr++) {
        printf("%s\n", *ptr); 
    }
    return 0;
}