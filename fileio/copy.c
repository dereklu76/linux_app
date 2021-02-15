#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
	int inputFd, outputFd, openFlags;
	mode_t filePerms;
	ssize_t numRead;
	char buf[BUF_SIZE];

	if(argc != 3 || strcmp(argv[1], "--help") == 0)
	{
		printf("Useage error! Format is %s old-file new-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/*Open input and output files*/

	inputFd = open(argv[1], O_RDONLY);
	if(inputFd == -1)
	{
		printf("Failed to open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
			S_IROTH | S_IWOTH;

	outputFd = open(argv[2], openFlags, filePerms);
	if(outputFd == -1)
	{
		printf("Failed to open file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	/*Transfer data until we encounter end of input or an error*/

	while((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
	{
		if(write(outputFd, buf, numRead) != numRead)
		{
			printf("could't write whole buffer\n");
			exit(EXIT_FAILURE);
		}
	}

	if(numRead == -1)
	{
		printf("Failed to read\n");
		exit(EXIT_FAILURE);
	}

	if(close(inputFd) == -1)
	{
		printf("Failed to close input\n");
		exit(EXIT_FAILURE);
	}

	if(close(outputFd) == -1)
	{
		printf("Failed to close output\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
































