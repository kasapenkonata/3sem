#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/sysmacros.h>
#include <sys/stat.h>
#include <time.h>
 
#define BUF_SIZE 1024


int main(int argc, char* argv[])
{
	int input_fd, output_fd;   
	ssize_t ret_in, ret_out;   
	char buffer[BUF_SIZE];
	struct stat stat_buf;
	int result;
	int was_written = 0;

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

	printf("Old file: \n");
	printf("Last status change:       %s", ctime(&stat_buf.st_ctime));
	printf("Last file access:         %s", ctime(&stat_buf.st_atime));
	printf("Last file modification:   %s", ctime(&stat_buf.st_mtime));


	if (!S_ISREG(stat_buf.st_mode))
	{
		printf("%s is not regular file", argv[1]);
		return 3;
	}


	input_fd = open (argv [1], O_RDONLY);

	if (input_fd == -1) 
	{
		printf ("Can't open file for reading %s\n%s\n", argv [1], strerror(errno));
		return 5;
	}

	output_fd = open(argv[2], O_WRONLY | O_CREAT, 00700);

	if(output_fd == -1)
	{
		printf ("Can't create file for whiting %s\n%s\n", argv [2], strerror(errno));
		close(input_fd);
		return 6;
	}

	do 
	{
		ret_in = read (input_fd, &buffer, BUF_SIZE);
 		was_written = 0;
		if (ret_in == -1)
		{
			perror("Unable to read");
			close(input_fd);
			close(output_fd);
			return 7;
		}
		do 
		{

		ret_out = write (output_fd, &buffer, (ssize_t) ret_in);
		was_written += ret_out;
		if (ret_out == -1)
	       		{
			printf ("Error during copy process\n%s\n", strerror(errno));
			return 8;
			}
		} while (was_written != ret_in);

	} while (ret_in != 0);


	if (fsync(output_fd) == -1)
    	{
		perror("Failed to fsync");
		return 9;
	}
	if (fchmod(output_fd, stat_buf.st_mode) == -1)
	{
		perror("Failed to fchmod");
		return 10;
	}

	struct timespec am_time[2] = {stat_buf.st_atim, stat_buf.st_mtim};

	if (futimens(output_fd, am_time) == -1)
	{
		perror("Failed to futimens");
		return 11;
	};


	if (lstat(argv[2], &stat_buf) == -1)
	{
		printf ("Failed to stat %s\n%s\n", argv [2], strerror(errno));                                                                                                              return 2;
	}

	printf("New file: \n");
	printf("Last status change:       %s", ctime(&stat_buf.st_ctime));
	printf("Last file access:         %s", ctime(&stat_buf.st_atime));
	printf("Last file modification:   %s", ctime(&stat_buf.st_mtime));

	result = close(input_fd);
	if (result == -1)
	{
		perror("unable to close input_fd");
		return 12;
	}

	result = close(output_fd);
	if (result == -1)
	{
		perror("unable to close output_fd");
		return 13;
	}

	return 0;
}
