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
	char operation;
	string fileNameACL;
	char *storeVal;
	int overWritePermission;
	FILE *newFile ;
	FILE *filestream;
	int val ;
	size_t dum;
	char * bufferReadIn;
	FILE *metaFile;
	FILE *aclList;

	printf("arc is %d, arv[0] is %s \n", argc , argv[0]);
	//char * objName = NULL;
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0 ;


	
	parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
		     , group,operation);
	
	if(uFlag != 1 || gFlag!= 1 || aFlag == 1 || lFlag == 1){
		perror("invalid argument input");
		exit(EXIT_FAILURE);
	}
		
	if(checkShellRedirect()){
		perror("There is no shell redirect. program stopped");
		exit(EXIT_FAILURE);
	}
	
	printf("the usr string is %s \n", usr.c_str());
	
	/*
	string str1("./objput");
	if(string(argv[0]).compare(str1) == 0){
		objName = (char *)malloc(sizeof(char)*(strlen(argv[argc-1])+1));
		strcpy(objName,argv[argc-1]);
	}*/
	
	string fileName(usr);
	addPathName(fileName,(char *)argv[argc-1],1,0,0);
	
	/*
	int FileLength;
	FileLength = strlen(argv[argc-1])+usr.length()+2;
	char *fileName = (char*) malloc(FileLength*sizeof(char));
	strcpy(fileName,usr.c_str());
	strcat(fileName,"+");
	strcat(fileName,argv[argc-1]);
	
	fileName[FileLength-1] = '\0';*/
	
	storeVal = NULL;
	filestream = fopen(fileName.c_str(),"r");
	if(filestream != NULL){
		fileNameACL.assign(fileName);
		addPathName(fileNameACL,NULL,0,1,0);

		findPermission(fileNameACL, (char *)usr.c_str(),
			       (char *)group.c_str(),&storeVal);
		printf("the permission file is %s \n", storeVal);
		
		overWritePermission = checkPermission('w',storeVal);
		free(storeVal);
		fclose(filestream);
		if(overWritePermission != 1){
			perror("we dont have overwrite permssion");
			exit(EXIT_FAILURE);
		}
	}
	
	newFile = fopen(fileName.c_str(),"w+");
	
	if(newFile == NULL)
		exit(EXIT_FAILURE);
	
	bufferReadIn = NULL;
	while((val = (int)getline(&bufferReadIn,&dum,stdin))!=-1){
		
		printf("\n the string is %s \n",bufferReadIn);
		fputs(bufferReadIn,newFile);
		free(bufferReadIn);
		bufferReadIn = NULL;
	}
	fclose(newFile);
	
	

	string metaFileName(usr);
	addPathName(metaFileName,NULL,0,0,1);
	cout<<metaFileName+"TT"<<endl;
	/*
	int metaFileLength = FileLength + strlen("meta")+2;
	char *metaFileName = (char *)malloc(metaFileLength*sizeof(char));
	
					    
	strcpy(metaFileName,fileName);
	strcat(metaFileName,"+");
	strcat(metaFileName,"meta");
	metaFileName[metaFileLength-1] = '\0';*/
	
	metaFile = fopen(metaFileName.c_str(),"r");
	
	if(metaFile == NULL){
		cout<<"getinC"<<endl;
		metaFile = fopen(metaFileName.c_str(),"w");
		fputs(usr.c_str(),metaFile);
		fputs(" ",metaFile);
		fputs(group.c_str(),metaFile);
		fclose(metaFile);
		cout<<"getinD"<<endl;

	}
	else
	{
		cout<<"getinA"<<endl;
		//cout<<"getinB"<<endl;
		if(checkGroupExist(metaFile, group.c_str())){
			cout<<"getinE"<<endl;
			fclose(metaFile);
		}
		else{
			cout<<"getinB"<<endl;
			fclose(metaFile);
			metaFile = fopen(metaFileName.c_str(),"a");
			fputs(" ", metaFile);
			fputs(group.c_str(),metaFile);
			fclose(metaFile);
		}
	}
	
	

	string aclListName(fileName);
	addPathName(aclListName,NULL,0,1,0);
	
	/*
	int aclListLength = FileLength + strlen("ACL")+2;
	char *aclListName = (char *)malloc(aclListLength*sizeof(char));
	strcpy(aclListName,fileName);
	strcat(aclListName,"+");
	strcat(aclListName,"ACL");*/
	
	aclList = fopen(aclListName.c_str(),"w+");
	if(aclList == NULL)
		exit(EXIT_FAILURE);
	fputs(usr.c_str(),aclList);
	fputs(".*	",aclList);
	fputs("rwxpv", aclList);
	fclose(aclList);
	
	
	
	
	//fputs("\0".metaFile);
	
	printf ("uflag = %d,aflag = %d, gflag = %d, lvalue = %d\n",
		uFlag,aFlag, gFlag, lFlag);
	printf("uval = %s, gVal = %s, aVal = %c", usr.c_str(),group.c_str(),
	       operation);
	
	
	return 0;
	
	
	// insert code here...
	
}




