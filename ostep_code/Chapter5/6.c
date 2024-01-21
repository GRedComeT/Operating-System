#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <assert.h>


// int main(int argc, char* argv[]) {
//     int rc = fork();
//     assert(rc >= 0);
//     if (rc == 0) {
//         printf("I'm child, pid = %d, now I call 'wait()'.\n", (int)getpid());
//         int rc_wait = wait(NULL);
//         printf("Also child, the rc_wait is %d.\n", rc_wait);
//     } else {
//         int rc_wait = waitpid(rc, NULL, 0);
//         printf("I'm parent, with pid = %d. I have been waited the child(%d)(rc_wait=%d).\n", (int)getpid(), rc, rc_wait);
//     }
//     return 0;
// }


int main(int argc, char* argv[]) {
    int childNumber = 5;
    int childProcess[5];
    for (int i = 0; i < childNumber; ++i) {
        int rc = fork();
        childProcess[i] = rc;
        if (rc == 0) {
            printf("I'm child, pid = %d, now I call 'wait()'.\n", (int)getpid());
            int rc_wait = wait(NULL);
            printf("Also child(%d), the rc_wait is %d.\n", (int)getpid(), rc_wait);
            exit(0);
        }
    }
    // You can use waitpid() and int[] childProcess to make more specific operating, like a unique child result, etc.
    // Here just simple wait() them in created sequence.
    for (int i = 0; i < childNumber; ++i) {
        waitpid(childProcess[((i + 3) % childNumber + childNumber) %childNumber], NULL, 0);
        printf("I'm parent, check child %d's return.\n", childProcess[((i + 3) % childNumber + childNumber) %childNumber]);
    }
    return 0;
}

// First question, see the man page about the 'wait()' family.
// Second question, waitpid() can be useful in situation where multi-child be created.