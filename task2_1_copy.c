/*
 * task 2.1 - open, read, write, close - for regular files, using dprintf
 **/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 128

int main(int argc, char* argv[]) 
{
	int input_fd, output_fd;
	ssize_t retin, retout;
	char buffer[BUF_SIZE];

	if (argc != 3) 
	{
		printf("Usage: read_file_name, write_file_name\n");
		return 1;
	}

	input_fd = open(argv[1], O_RDONLY);
	if (input_fd == -1)
	{
		printf("Can't open file for reading");
		return 2;
	}

	output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
	if (output_fd == -1)
	{
		printf("Can't write into the file");
		return 3;
	}

	while ((retin = read(input_fd, &buffer, BUF_SIZE)) > 0)
	{
		for (size_t i = 0; i < retin; i++) 
		{
			dprintf(output_fd, "%c", buffer[i]);
		}
	}

	close(input_fd);
	close(output_fd);

	return 0;
}
