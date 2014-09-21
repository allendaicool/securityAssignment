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
	string operation;
	int result;
	struct dirent *entry;
	struct stat st;;
	
	printf("arc is %d, arv[0] is %s \n", argc , argv[0]);
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0 ;
	result = parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
			      , group,operation);
	printf ("uflag = %d,aflag = %d, gflag = %d, lvalue = %d\n",
		uFlag,aFlag, gFlag, lFlag);
	printf("uval = %s, aVal = %s, gVal = %s", usr.c_str(),group.c_str(),
	       operation.c_str());
	
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
			off_t size;
			stat(entry->d_name, &st);
			size = st.st_size;
			printf(" %s     %lld\n bytes ",entry->d_name,size);
			
		}
	}
	return 0 ;
}