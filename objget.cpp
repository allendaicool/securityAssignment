//
//  objget.cpp
//  
//
//  Created by yihong dai on 9/20/14.
//
//

#include "objget.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <getopt.h>
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
	printf("arc is %d, arv[0] is %s \n", argc , argv[0]);
	//char * objName = NULL;
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0 ;
	result = parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
			      , group,operation);
	
	printf ("uflag = %d,aflag = %d, gflag = %d, lvalue = %d\n",
		uFlag,aFlag, gFlag, lFlag);
	printf("uval = %s, aVal = %s, gVal = %s", usr.c_str(),group.c_str(),
	       operation.c_str());
	
	
	FILE *filestream;
	int fileLength = strlen(usr.c_str()) + strlen(argv[argc-1]) + 2 ;
	char * fileName = (char * ) malloc(fileLength * sizeof(char));
	strcpy(fileName, usr.c_str());
	strcat(fileName,"+");
	strcat(fileName,argv[argc-1]);
	fileName[fileLength-1] = '\0';
		
	int fileLengthACL = strlen(fileName) + strlen("ACL") + 2 ;
	char * fileNameACL = (char * ) malloc(fileLengthACL * sizeof(char));
	strcpy(fileNameACL, fileName);
	strcat(fileNameACL,"+");
	strcat(fileNameACL,"ACL");
	fileNameACL[fileLengthACL-1] = '\0';
	char * val = NULL;
	string FileNameString(fileNameACL);
	findPermission(FileNameString, (char *)usr.c_str(),(char *)group.c_str()
		       ,&val);
	printf("the permission file is %s \n", val);
	int loop;
	int readPermission;
	readPermission = -1 ;
	for(loop = 0; loop < strlen(val);loop++)
	{
		if(val[loop] =='r')
		{
			readPermission = 1;
			break;
		}
	}
	if(readPermission == 1)
	{
		printf("we have read permission");
		filestream = fopen(fileName,"r");
		if(filestream == NULL)
		{
			printf("no suc file\n");
			exit(EXIT_FAILURE);
		}
		char *buffer = NULL;;
		size_t dum;
		int revalue;
		puts("\n");
		while((revalue = (int)getline(&buffer,&dum,filestream))!= -1)
		{
			puts(buffer);
		}
		if(buffer)
		{
			free(buffer);
		}
		fclose(filestream);
	}
	else
	{
		perror("we dont have read permssion");
		exit(EXIT_FAILURE);
	}
	
	return 0;
	
}