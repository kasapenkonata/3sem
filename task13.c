#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

int info()
{	
	printf("process ID: %d\n", getpid());
	printf("process parent's ID: %d\n", getppid());
	struct passwd *user;
	user = getpwuid(getuid());
	if (!user)
	{
		perror("ERROR");
		return 1;
	}


	printf("User ID:, %d\n", user->pw_uid);
	printf("User name: %s\n", user->pw_name);
	printf("User password: %s\n", user->pw_passwd);
	printf("User information: %s\n", user->pw_gecos);
	printf("Group id: %d\n", user->pw_gid);
	printf("Home directory: %s\n", user->pw_dir);


	struct group *group;
	group = getgrgid(user->pw_gid);
	if (!group)
	{
		perror("ERROR");
		return 2;
	}

	printf("Group id: %d\n", group->gr_gid);
	printf("Group name: %s\n", group->gr_name);
	return 0;

}

int main()
{
	pid_t child_id = fork();
	switch (child_id)
	{
		case -1:
			perror("unable to born a fork");
			return 1;
		case 0:
			printf("child:\n");
			info();
			return 0;
		default:
			wait(NULL);
			printf("parent:\n");
			info();	
			return 0;	
	}
		    return 0;
}
