#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int fd;

    fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL);

    sleep(5);

    if(fd != -1)
    {
        printf("[PID %ld] File \"%s\" already exists\n", 
            (long)getpid(), argv[1]);
        close(fd);
    }
    else
    {
        if(errno != EEXIST) /*Failed for unexpected reason*/
        {
            printf("Failed to open!\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("[PID %ld] Created file \"%s\" exclusively\n",
                (long)getpid(), argv[1]);       
        }
    }

    exit(EXIT_SUCCESS);
}