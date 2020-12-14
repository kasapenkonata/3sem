/*
 * task 3.1 - open, read, write, close, checks if file is regular*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
 
#define BUF_SIZE 128
 
int main(int argc, char* argv[])
{
	int input_fd, output_fd;   
	ssize_t ret_in, ret_out;   
	char buffer[BUF_SIZE], buffer_copy[BUF_SIZE];
	struct stat stat_buf;
	if(argc != 3)
	{
		printf ("Usage: cp read_file_name write_file_name\n");
		return 1;
	}		        
	if (lstat(argv[1], &stat_buf) == -1)
	{
		printf ("Failed to stat %s\n%s\n", argv [1], strerror(errno));
		return 2;
	}

	if (S_ISREG(stat_buf.st_mode) == 0)
	{
		printf("%s is not simple file", argv[1]);
		return 3;
	}
	if (lstat(argv[2], &stat_buf) == -1)
	{
		printf ("Failed to stat %s\n%s\n", argv [2], strerror(errno));
		return 2;
	}

      	if (S_ISREG(stat_buf.st_mode) == 0)
	{
		printf("%s is not simple file", argv[2]);
		return 4;
	}
	
	input_fd = open (argv [1], O_RDONLY);
	if (input_fd == -1) 
	{
		printf ("Can't open file for reading %s\n%s\n", argv [1], strerror(errno));
		return 5;
	}
						   
	output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
	if(output_fd == -1)
	{
		printf ("Can't create file for whiting %s\n%s\n", argv [2], strerror(errno));
		return 6;
	}

	while((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0)
	{
		ret_out = write (output_fd, &buffer, (ssize_t) ret_in);
		if(ret_out != ret_in) 
		{
			printf ("Error during copy process\n%s\n", strerror(errno));
			return 7;																     
		}
	}	
		close (input_fd);
		close (output_fd);

	return 0;
}