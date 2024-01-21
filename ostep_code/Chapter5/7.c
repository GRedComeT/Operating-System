#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <assert.h>


int main(int argc, char* argv[]) {
    int rc = fork();
    assert(rc >= 0);
    if (rc == 0) {
        printf("I'm child, pid = %d, now I close STDOUT_FILENO.\n", (int)getpid());
        close(STDOUT_FILENO);
        printf("After I close, what happened?\n");
    } else {
        int rc_wait = waitpid(rc, NULL, 0);
        printf("I'm parent, with pid = %d. The child(%d) close the STDOUT_FILENO, what will happen?\n", (int)getpid(), rc);
    }
    return 0;
}

// When child close the STDOUT_FILENO, the output can not be seen in terminal. And will not affect parent due to there are different
// process with own process state.