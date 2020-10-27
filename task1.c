#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

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

	printf("Mode: %06o \n Size: %llu \n Used space: %llu \n User_id: %llu\n Group_id: %llu\n",
			(unsigned int) stat_buf.st_mode, 
			(unsigned long long) stat_buf.st_size, 
			(unsigned long long) stat_buf.st_blocks * 512,
			(unsigned long long) stat_buf.st_uid,
			(unsigned long long) stat_buf.st_gid);
}

