 #include <stdio.h>
 #include <dirent.h>
 #include <errno.h>
 #include <string.h>
 #include <sys/types.h>
 #include <sys/stat.h>

char* dir_type(int type)
{
	switch (type)
	{
		case DT_FIFO:   return "FIFO";                  break;
		case DT_CHR:    return "CHARACTER SPECIAL";     break;
		case DT_DIR:    return "DIRECTORY";             break;
		case DT_BLK:    return "BLOCK SPECIAL";         break;
		case DT_REG:    return "REGULAR";               break;
		case DT_LNK:    return "SYMBOLIC LINK";         break;
		case DT_SOCK:   return "SOCKET";                break;
		case DT_WHT:    return "WHITEOUT";              break;
		default: return "unknown?";                     break;
	}
}

char* get_type(struct stat sb)
{
	switch (sb.st_mode & S_IFMT)
	{
		case S_IFBLK:  return "block device"; 
		case S_IFCHR:  return "character device";
		case S_IFDIR:  return "directory";
		case S_IFIFO:  return "FIFO/pipe";
		case S_IFLNK:  return "symlink";
		case S_IFREG:  return "regular file";
		case S_IFSOCK: return "socket";
		default:       return "unknown?";
	}
	return 0;
}

int main (int argc, char *argv[]) 
	{
	       	struct dirent *pDirent;
            	DIR *pDir;
            	char *dirName;
           	struct stat sb;
		int result = 0;

            	if (argc == 1) 
		{
                	dirName = ".";
	        } 
		else 
		{
            		if (argc != 2) 
			{
                   		printf ("Usage: programm <dirname>\n");
                    		return 1;
              		}
            	dirName = argv[1];
	        }

           	pDir = opendir (dirName);
           	if (pDir == NULL) 
		{
                	printf ("Cannot open directory %s\n%s\n", dirName, strerror(errno));
			return 2;
	        }
		
	   	printf("Entire directory %s:\n", dirName);
	   	printf("%30s %15s\n",  "Type", "Name");

	   	while ((pDirent = readdir(pDir)) != NULL) 
		{
	  		 if (lstat(pDirent->d_name, &sb) == -1)
			 {
	      			printf ("Failed to stat %s\n%s\n", pDirent->d_name, strerror(errno));
	              		return 3;
	           	 }
			
			 if (pDirent->d_type == DT_UNKNOWN)
			 {
				printf ("%30s %15s\n", get_type(sb), pDirent->d_name);
			 }
			 else 
			 {
				 if (lstat(pDirent->d_name, &sb) == -1)
				 {
					 printf ("Failed to stat %s\n%s\n", pDirent->d_name, strerror(errno));					
					 return 3;
				 }					 
				 printf ("%30s %15s\n", dir_type(pDirent->d_type), pDirent->d_name);
			 }
		}

	        result = closedir (pDir);
		if (result == -1)
		{
			perror("Unable to close dir");
			return 3;
		}
	        return 0;
	}
