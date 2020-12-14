 #include <stdio.h>
 #include <dirent.h>
 #include <errno.h>
 #include <string.h>
 #include <sys/types.h>
 #include <sys/stat.h>

int main (int argc, char *argv[]) 
	{
	       	struct dirent *pDirent;
            	DIR *pDir;
            	char *dirName;
           	struct stat sb;
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
	   	printf("%30s%15s%20s\n", "Name", "Type", "Size");
	   	while ((pDirent = readdir(pDir)) != NULL) 
		{
	  		 if (lstat(pDirent->d_name, &sb) == -1)
			 {
	      			printf ("Failed to stat %s\n%s\n", pDirent->d_name, strerror(errno));
	              		return 3;
	           	 }  
	        	 printf ("%30s%15d%20u bytes\n", pDirent->d_name, pDirent->d_type, (unsigned)sb.st_size);
		}

	        closedir (pDir);
	        return 0;
	}
