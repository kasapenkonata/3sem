/**
 * task 2 - open, read, write, close*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
 
#define BUF_SIZE 100
 
int main (int argc, char* argv[]) 
{
	 int input_fd, output_fd;  
         ssize_t ret_in, ret_out; //ret_in - amount of read char, ret_out - amount of written char 
	 char buffer[BUF_SIZE];  
		     
		   
	 if(argc != 3) 
	 {
		 printf ("Usage: cp read_file_name write_file_name\n");
		 return 1;
	 }
			 
	 input_fd = open (argv [1], O_RDONLY);
         if (input_fd == -1) 
	 {
		printf ("Can't open file for reading %s\n", argv [1]);
		return 2;
	 }
				 
	 output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
	 if(output_fd == -1)
	 {
	 	printf ("Can't create file for whiting %s\n", argv [2]);
	 	return 3;
	 }

	 while ((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0) 
	 {
		ret_out = write (output_fd, &buffer, (ssize_t) ret_in);
		if (ret_out != ret_in) 
		{
		printf ("Error during copy process\n");
		return 4;							     
		}
	 }
					     
		close (input_fd);
		close (output_fd);
						     
		return 0;
	}