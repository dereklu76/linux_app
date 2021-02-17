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

    fd = open(argv[1], O_WRONLY);

    sleep(5);

    if(fd != -1)
    {
        printf("[PID %ld] File \"%s\" already exists\n", 
            (long)getpid(), argv[1]);
        close(fd);
    }
    else
    {
        if(errno != ENOENT) /*Failed for unexpected reason*/
        {
            printf("Failed to open!\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            /*WINDOW FOR FAILURE*/
            fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
            if(fd == -1)
            {
                printf("Failed to open!\n");
                exit(EXIT_FAILURE);
            }

            printf("[PID %ld] Created file \"%s\" exclusively\n",
                (long)getpid(), argv[1]);       /*MAY NOT BE TRUE!*/
        }
    }

    exit(EXIT_SUCCESS);
}