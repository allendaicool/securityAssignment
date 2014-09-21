//
//  objlist.cpp
//  
//
//  Created by yihong dai on 9/20/14.
//
//
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>




int main(int argc, const char * argv[])
{
	
	struct dirent *entry;

	
	DIR *currentDir;
	char *currentDirName = "./";
	if ((currentDir = opendir(currentDirName)) == NULL)
	{
		// exit if problem in opening directory
		perror("opendir() error");
		exit(EXIT_FAILURE);
	}
	while ((entry = readdir(currentDir)) != NULL )
		{
			printf("the filename is %s \n", (char *)(entry->d_name));
		}
	printf("the direcotry name is %s ", currentDirName);
	return 0 ;
}