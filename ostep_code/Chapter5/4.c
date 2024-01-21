#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

// int main(int argc, char* argv[]) {
//     int rc = fork();
//     assert(rc >= 0);
//     if (rc == 0) {
//         printf("I'm child, pid=%d, now I will change to 'wc' function to '4.c'.\n", (int)getpid());
//         if (*argv[1] == '0') {
//             // execvp style
//             char* myargv[3];
//             myargv[0] = "wc";
//             myargv[1] = "4.c";
//             myargv[2] = NULL;
//             execvp(myargv[0], myargv); 
//         } else if (*argv[1] == '1') {
//             // execlp style
//             execlp("wc", "wc", "4.c", NULL);
//         }
        
//     } else {
//         int rc_wait = wait(NULL);
//         printf("I'm parent, pid=%d, and child pid=%d, Say Goodbye.\n", (int)getpid(), rc);
//     }
//     return 0;
// }


int main(int argc, char* argv[]) {
    int rc = fork();
    assert(rc >= 0);
    if (rc == 0) {
        printf("I'm child, pid=%d, now I will change environ function to 'test4.c'.\n", (int)getpid());
        if (*argv[1] == '0') {
            // do not change environ
            char* myargv[3];
            myargv[0] = "./test4";
            myargv[1] = "./test4";
            myargv[2] = NULL;
            execvp(myargv[0], myargv); 
        } else if (*argv[1] == '1') {
            // change the environ
            char* myargv[3];
            myargv[0] = "./test4";
            myargv[1] = "./test4";
            myargv[2] = NULL;
            char* myenv[] = {"AA=BB", "CC=DD", NULL};
            #define _GNU_SOURCE
            execvpe(myargv[0], myargv, myenv); 
        }
        
    } else {
        int rc_wait = wait(NULL);
        printf("I'm parent, pid=%d, and child pid=%d, Say Goodbye.\n", (int)getpid(), rc);
    }
    return 0;
}


// By reading man page, we can think the 'exec()' family with every single parameters.
// for 'l' ('execl()'), which means the form of arguments is 'list' compared to 'vector' in parameter 'v' ('execv()')
// for 'p', which means whether searching in the 'PATH' if the first argument 'char *file' do not contain slash(/).
// In contrast, we can say if the first argument contains slash, the behaviour with or without 'p' is the same.
// for 'e', which means change the enviroment of new process by 'extern char** environ'.


