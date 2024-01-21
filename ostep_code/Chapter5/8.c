#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <assert.h>


int main(int argc, char* argv[]) {
    int pipefd[2];
    char buf;
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 2; ++i) {
        int rc = fork();
        assert(rc >= 0);
        if (rc == 0) {
            if (i == 0) {
                close(pipefd[0]);
                printf("I'm child #1, I will write some string to child #2.\n");
                char* s = "Hello my bro.\n";
                write(pipefd[1], s, strlen(s));
                close(pipefd[1]);
                printf("I'm child #1, I've been writting something to child #2. Now I'm out.\n");
            } else {
                close(pipefd[1]);
                printf("I'm child #2, I will receive some words from child #1 and show it:\n");
                while (read(pipefd[0], &buf, 1) > 0) {
                    write(STDOUT_FILENO, &buf, 1);
                }
                printf("I'm child #2, now I will out.\n");
                close(pipefd[0]);
            }
            exit(EXIT_SUCCESS);
        }
    }

    // DO NOT FORGET CLOSE PIPE FD IN PARENT, WHICH WILL LEAD DEADLOCK.
    close(pipefd[0]);
    close(pipefd[1]);

    int n = 2;
    while (n > 0) {
        wait(NULL);
        n--;
    }

    return 0;
}

// Notice that do not forget close pipefd in parent. Considering the pipeline:
// parent -> child #2 -> child #1. And I think the OS scheduler will automatically sync due to pipe still open.
// For parent, create child #1 -> create child #2 -> [] -> wait() two child.
// For child #2, close its write pipefd, read from pipe which is empty; but there are still have some open write pipefd, so that 
// the scheduler determine child #2 to wait until pipe unempty.
// For child #1, close its read pipefd, write something, close its write pipefd and exit(). Then control back to child #2.
// For child #2 again, it read from pipe by read pipefd. But when pipe become empty, and parent will not close its pipefd, DEADLOCK!
// So we need to close the parent pipefd in '[]' part if we need not some information from child pass through kernel pipe. 

