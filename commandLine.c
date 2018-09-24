#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
int commandLine(int c, char *v[])
{
	printf("Inside command line function");
	int cLarg=open("/proc/5189/cmdline", O_RDONLY)  ;
	printf("hello cline\n");
	if(cLarg<0)
	{
		printf("error!!\n");
		return 0;
	}
	else
	{
		printf("commandLine=%d\n", cLarg);
	}
	{
	char *c = (char *) calloc(100, sizeof(char)); 
	
	
	if (cLarg < 0) { perror("r1"); exit(1); } 
	
	int sz = read(cLarg, c, 10); 
	printf("called read(% d, c, 10). returned that"
					" %d bytes were read.\n", cLarg, sz); 
	c[sz] = '\0'; 
	printf("Those bytes are as follows: % s\n", c); 
	}

	return 1;
}
