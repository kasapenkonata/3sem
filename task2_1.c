#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) 
{
	int output_fd;
	char* message;
	int message_len;

	if (argc != 3) 
	{
		printf("Usage:  write_file_name\n");
		return 1;
	}

	output_fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
	if (output_fd == -1)
	{
		printf("Can't create file for writing");
		return 2;
	}

	message_len = strlen(argv[2]);
	
	for (size_t i = 0; i < message_len; i++) 
	{
		dprintf(output_fd, "%c", argv[2][i]);
	}

	close(output_fd);

	return 0;
}
