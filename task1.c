#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

#define S_BLKSIZE 512

int main (int argc, char *argv[])
{
	if (argc != 2) 
	{
		printf("Usage: %s some.file\n", argv[0]);
		return 1;
	}

	struct stat stat_buf;

	if (lstat(argv[1], &stat_buf) == -1)
	{
		perror("Failed to stat");
		return 2;
	}                                        

    printf("Mode: %06o \nSize: %llu \nUsed space: %llu \nUser_id: %u\nGroup_id: %u\n",
			(unsigned int) stat_buf.st_mode, 
			(long long unsigned) stat_buf.st_size, 
			(long long unsigned) stat_buf.st_blocks * S_BLKSIZE,
			(unsigned int) stat_buf.st_uid,
			(unsigned int) stat_buf.st_gid);

     printf("File type:");
     switch (stat_buf.st_mode & S_IFMT)
     {
         case S_IFBLK: printf("block device\n"); 
                    break;
         case S_IFCHR: printf("character device\n");
                    break;
         case S_IFDIR: printf("directory\n");
                    break;
         case S_IFIFO: printf("FIFO/pipe\n");
                    break;
         case S_IFLNK: printf("symlink\n");
                    break;
         case S_IFREG: printf("regular file\n");
                    break;
         case S_IFSOCK: printf("socket\n");
                    break;
         default: printf("inknown type\n");   
     }
}
