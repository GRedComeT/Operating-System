#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>


// int main(int argc, char* argv[]) {
//     int x = 100;
//     int rc = fork();
//     assert(rc >= 0);
//     if (rc == 0) {
//         printf("I'm child, pid=%d, and the value of x is %d.\n", (int)getpid(), x);
//     } else {
//         int rc_wait = wait(NULL);
//         printf("I'm parent, pid=%d(rc_wait=%d), and child pid=%d, the value of x is %d.\n", (int)getpid(), rc, rc_wait, x);
//     }
//     return 0;
// }



// int main(int argc, char* argv[]) {
//     int x = 100;
//     int rc = fork();
//     assert(rc >= 0);
//     if (rc == 0) {
//         printf("I'm child, pid=%d, and the value of x is %d.\n", (int)getpid(), x);
//         x = 105;
//         printf("I'm child, pid=%d, and the value of x is %d(changed).\n", (int)getpid(), x);
//     } else {
//         int rc_wait = wait(NULL);
//         printf("I'm parent, pid=%d(rc_wait=%d), and child pid=%d, the value of x is %d(child changed).\n", (int)getpid(), rc, rc_wait, x);
//     }
//     return 0;
// }

int main(int argc, char* argv[]) {
    int x = 100;
    int rc = fork();
    assert(rc >= 0);
    if (rc == 0) {
        printf("I'm child, pid=%d, and the value of x is %d.\n", (int)getpid(), x);
        x = 105;
        printf("I'm child, pid=%d, and the value of x is %d(changed).\n", (int)getpid(), x);
    } else {
        
        printf("I'm parent, pid=%d, and child pid=%d, the value of x is %d(child changed).\n", (int)getpid(), rc, x);
    }
    return 0;
}

// easy and simple, because the child and parent is different process, i.e., private register, stack, and heap of process data.

// Remove the 'wait()' and executing the program 100 times, but the sequence of output are fixed (First
// parent, then child)due to the ubuntu's OS scheduler?