#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char* argv[])
{
	printf("process ID: %d\n", getpid());
	printf("process parent's ID: %d\n", getppid());

	struct passwd *user;
	user = getpwuid(getuid()); /*returns pointer to structure user or NULL if ERROR*/
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

