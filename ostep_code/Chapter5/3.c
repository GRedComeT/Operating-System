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
    int fd = open("2.output", O_RDWR|O_CREAT|O_TRUNC);
    int rc = fork();
    char buffer[80]; 
    assert(rc >= 0);
    if (rc == 0) {
        char s[] = "I'm child, writing something.\n";
        printf("I'm child, pid=%d, file descriptor=%d, Then writing string to file.\n", (int)getpid(), fd);
        write(fd, s, sizeof(s));
        close(fd);
    } else {
        int rc_wait = wait(NULL);
        char s[] = "I'm parent, writing something.\n";
        lseek(fd, 0, SEEK_SET);
        read(fd, buffer, sizeof(buffer));
        printf("I'm parent, pid=%d(rc_wait=%d), and child pid=%d, "
        "file descriptor=%d, the file content before writing: %s\nThen writing string to file.\n", (int)getpid(), rc_wait, rc, fd, buffer);
        write(fd, s, sizeof(s));
        close(fd);
    }
    return 0;
}

