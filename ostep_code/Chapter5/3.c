#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int rc = fork();
    char buffer[80]; 
    assert(rc >= 0);
    if (rc == 0) {
        printf("I'm child, pid=%d, Say Hello.\n", (int)getpid());
    } else {
        sleep(5);
        printf("I'm parent, pid=%d, and child pid=%d, Say Goodbye.\n", (int)getpid(), rc);
    }
    return 0;
}

// Just simple using 'sleep()' to make the OS scheduler determine next process (child) if the parent process faster than child.