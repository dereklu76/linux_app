#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
	size_t len;
	off_t offset;
	int fd, ap, j;
	char *buf;
	ssize_t numRead, numWritten;

	if(argc < 3 || strcmp(argv[1], "--help") == 0)
	{
		printf("Usage fault!\n");
		printf("%s file {r<length>|R<length>|w<string>|s<offset>}...\n", 
				argv[0]);
		exit(EXIT_FAILURE);
	}	

	fd = open(argv[1], O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
			S_IROTH | S_IWOTH);

	if(fd == -1)
	{
		printf("Failed to open!\n");
		exit(EXIT_FAILURE);
	}

	for(ap = 2; ap < argc; ap++)
	{
		switch(argv[ap][0])
		{
			case 'r':	/*Display bytes at current offset, as text*/
			case 'R':	/*Display bytes at current offset, in hex*/
				len = atol(&argv[ap][1]);
				buf = malloc(len);
				if(buf == NULL)
				{
					printf("Failed to malloc!\n");
					exit(EXIT_FAILURE);
				}

				numRead = read(fd, buf, len);
				if(numRead == -1)
				{
					printf("Failed to read!\n");
					exit(EXIT_FAILURE);
				}

				if(numRead == 0)
				{
					printf("%s: end-of-file\n", argv[ap]);
				}
				else
				{
					printf("%s: ", argv[ap]);
					for(j = 0; j < numRead; j++)
					{
						if(argv[ap][0] == 'r')
						{
							printf("%c", isprint((unsigned char)buf[j]) ? buf[j] : '?');
						}
						else
						{
							printf("%02x ", (unsigned int) buf[j]);
						}
					}
					printf("\n");
				}

				free(buf);
				break;

			case 'w':	/*Write string at current offset*/
				numWritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
				if(numWritten == -1)
				{
					printf("Failed to write!\n");
					exit(EXIT_FAILURE);
				}
				printf("%s: wrote %ld bytes\n", argv[ap], (long) numWritten);
				break;
			
			case 's':
				offset = atol(&argv[ap][1]);
				if(lseek(fd, offset, SEEK_SET) == -1)
				{
					printf("Failed to lseek!\n");
					exit(EXIT_FAILURE);
				}
				printf("%s: seek succeeded\n", argv[ap]);
				break;

			default:
				printf("Argument must start with [rRws]: %s\n", argv[ap]);
				exit(EXIT_FAILURE);
				break;
		}
	}

	exit(EXIT_SUCCESS);
}















