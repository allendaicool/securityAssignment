//
//  objlist.cpp
//  
//
//  Created by yihong dai on 9/20/14.
//
//

#include "objlist.h"
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include "functionCall.h"

using namespace std;


int main(int argc, const char * argv[])
{
	int  uFlag;
	int  gFlag ;
	int  aFlag;
	int  lFlag;
	string usr ;
	string group;
	char operation;
	struct dirent *entry;
	struct stat st;;
	
	printf("arc is %d, arv[0] is %s \n", argc , argv[0]);
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0 ;
	parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
			      , group,operation);
	
	if(uFlag != 1 || gFlag== 1 || aFlag == 1 ){
		perror("invalid argument input");
		exit(EXIT_FAILURE);
	}
	printf ("uflag = %d,aflag = %d, gflag = %d, lvalue = %d\n",
		uFlag,aFlag, gFlag, lFlag);
	printf("uval = %s, gVal = %s, aVal = %c", usr.c_str(),group.c_str(),
	       operation);
	
	DIR *currentDir;
	char *currentDirName = (char *)"./";
	if ((currentDir = opendir(currentDirName)) == NULL)
	{
		// exit if problem in opening directory
		perror("opendir() error");
		exit(EXIT_FAILURE);
	}
	printf("the begin \n");
	while ((entry = readdir(currentDir)) != NULL )
	{
		if(strstr(entry->d_name,usr.c_str()) != NULL &&
		   strstr(entry->d_name,"ACL") == NULL&&
		   strstr(entry->d_name,"meta") == NULL){
			int size;
			stat(entry->d_name, &st);
			size = (int)st.st_size;
			char * toBeprint = (char *)malloc(sizeof(char)*(
					strlen(entry->d_name)+1));
			strcpy(toBeprint,entry->d_name);
			toBeprint[strlen(entry->d_name)] = '\0';
					
			char *limiter = (char *)"+";
			char *firstName = strtok(toBeprint,limiter);
			firstName = strtok(NULL,limiter);
			if(lFlag)
				printf(" %s     %d\n bytes ",firstName,size);
			else
				printf(" %s \n bytes ",firstName);

			if(toBeprint)
				free(toBeprint);
			
		}
	}
	return 0 ;
}
