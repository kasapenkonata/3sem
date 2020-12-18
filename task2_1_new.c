#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
 
#define BUF_SIZE 1024
 
int main (int argc, char* argv[]) 
{
	     int output_fd;    /* Input and output file descriptors */
	              ssize_t ret_in, ret_out;    /* Number of bytes returned by read() and write() */
		           char buffer[BUF_SIZE];      /* Character buffer */
			                
			                   /* Are src and dest file name arguments missing */
			        if(argc != 2) 
					     {
						              printf ("Usage: cp write_file_name\n");
							               return 1;
								            }
				             
				     output_fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
				          if(output_fd == -1)
						       {
							                printf ("Can't create file for whiting %s\n", argv [1]);
									         return 3;
										      }
					      dprintf(output_fd , "%20s%5d", "Task balls:", 10);
					                   
					          close (output_fd);
						                           
						      return (0);
}
