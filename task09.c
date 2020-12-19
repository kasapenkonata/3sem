#include <stdio.h>
#include <sys/param.h>
#include <sys/mount.h>
#include <sys/statvfs.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s file\n", argv[0]);
		return 1;
	}

	struct statvfs bufer;
	if (statvfs(argv[1], &bufer) == -1)
	{
		perror("Failed to statvfs\n");
		return 1;
	}

	printf("Size total: %lu\n", bufer.f_bsize*bufer.f_blocks);
	printf("Size available for unpriviled user:  %lu\n", bufer.f_bsize*bufer.f_bavail);
	printf("Size available in filesystem: %lu\n", bufer.f_bsize * bufer.f_bfree);
	printf("Size used2: %lu\n", bufer.f_bsize * (bufer.f_blocks - bufer.f_bfree));
	return 0;
}
