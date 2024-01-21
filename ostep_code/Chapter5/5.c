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
        printf("I'm child, pid = %d, now I call 'wait()'.\n", (int)getpid());
        int rc_wait = wait(NULL);
        printf("Also child, the rc_wait is %d.\n", rc_wait);
    } else {
        int rc_wait = wait(NULL);
        printf("I'm parent, with pid = %d. I have been waited the child(%d)(rc_wait=%d).\n", (int)getpid(), rc, rc_wait);
    }
    return 0;
}

// If the child call the 'wait()', it will return '-1' because there is no other process ready except its parent.
// When I check the man page, I found what I explain have a little problem. The 'wait()' family is just wait the caller's child,
// so that if there is no child, return '-1' immediately.