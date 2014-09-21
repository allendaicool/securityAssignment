//
//  main.cpp
//  cs4187
//
//  Created by yihong dai on 9/18/14.
//  Copyright (c) 2014 yihong dai. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <getopt.h>
#include "help.h"
#include "functionCall.h"
using namespace std;

int main(int argc, const char * argv[])
{
	int  uFlag;
	int  gFlag ;
	int  aFlag;
	int  lFlag;
	
	
	/*
	char *usr = NULL;
	char *group =  NULL;
	char *operation = NULL;*/
	string usr ;
	string group;
	string operation;
	
	
	
	int result;
	printf("arc is %d, arv[0] is %s \n", argc , argv[0]);
	char * objName = NULL;
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0 ;

	
	
	
	
	result = parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
		     , group,operation);
	
	printf("the usr string is %s \n", usr.c_str());
	
	
	string str1("./objput");
	if(string(argv[0]).compare(str1) == 0){
		objName = (char *)malloc(sizeof(char)*(strlen(argv[argc-1])+1));
		strcpy(objName,argv[argc-1]);
	}
	FILE *newFile ;
	int FileLength;
	FileLength = strlen(argv[argc-1])+usr.length()+2;
	char *fileName = (char*) malloc(FileLength*sizeof(char));
	strcpy(fileName,usr.c_str());
	strcat(fileName,"+");
	strcat(fileName,argv[argc-1]);
	
	fileName[FileLength-1] = '\0';
	
	newFile = fopen(fileName,"w+");
	
	if(newFile == NULL)
		exit(EXIT_FAILURE);
	int val ;
	size_t dum;
	char * bufferReadIn = NULL;
	while((val = (int)getline(&bufferReadIn,&dum,stdin))!=-1){
		
		printf("\n the string is %s \n",bufferReadIn);
		fputs(bufferReadIn,newFile);
		free(bufferReadIn);
		bufferReadIn = NULL;
	}
	fclose(newFile);
	FILE *metaFile;
	int metaFileLength = FileLength + strlen("meta")+2;
	char *metaFileName = (char *)malloc(metaFileLength*sizeof(char));
	
					    
	strcpy(metaFileName,fileName);
	strcat(metaFileName,"+");
	strcat(metaFileName,"meta");
	metaFileName[metaFileLength-1] = '\0';
	
	metaFile = fopen(metaFileName,"w+");
	if(metaFile == NULL)
		exit(EXIT_FAILURE);
	fputs(usr.c_str(),metaFile);
	fputs(" ",metaFile);
	fputs(group.c_str(),metaFile);
	fclose(metaFile);
	
	FILE *aclList;
	int aclListLength = FileLength + strlen("ACL")+2;
	char *aclListName = (char *)malloc(aclListLength*sizeof(char));
	strcpy(aclListName,fileName);
	strcat(aclListName,"+");
	strcat(aclListName,"ACL");
	aclList = fopen(aclListName,"w+");
	if(aclList == NULL)
		exit(EXIT_FAILURE);
	fputs(usr.c_str(),aclList);
	fputs(".*	",aclList);
	fputs("rwxpv", aclList);
	fclose(aclList);
	
	
	
	
	//fputs("\0".metaFile);
	
	printf ("uflag = %d,aflag = %d, gflag = %d, lvalue = %d\n",
		uFlag,aFlag, gFlag, lFlag);
	printf("uval = %s, aVal = %s, gVal = %s", usr.c_str(),group.c_str(),
	       operation.c_str());
	
	
	return 0;
	
	
	// insert code here...
	
}




