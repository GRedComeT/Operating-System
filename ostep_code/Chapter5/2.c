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
    int fd = open("2.output", O_RDWR|O_CREAT|O_TRUNC|O_SYNC);
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

// Both processes can write in a right way, but can not read concurrently. I think it is the file write and read way about the file
// descriptor, which would be learnt in **Persistence**? Because I move the file offset by 'lseek()' everything become right. 
// Simple said by chatGPT, even if each process has its own fd, but it point to the same file offset and status flag, or meta information.
// When child call 'write()', the file offset change; that's why parent read nothing utill 'lseek()' to remove offset in start of file.