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
	//FILE *metaFile;
	FILE *aclList;

	printf("arc is %d, arv[0] is %s \n", argc , argv[0]);
	
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0 ;


	
	parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
		     , group,operation);
	
	checkifUserGroup((char *)usr.c_str(), (char *)group.c_str(),0);
	
	if(uFlag != 1 || gFlag!= 1 || aFlag == 1 || lFlag == 1){
		fprintf(stderr, "invalid argument input\n");		
		//perror("invalid argument input");
		exit(EXIT_FAILURE);
	}
		
	if(checkShellRedirect()){
		fprintf(stderr, "There is no shell redirect. program stopped\n");		
		//perror("There is no shell redirect. program stopped");
		exit(EXIT_FAILURE);
	}
	
	printf("the usr string is %s \n", usr.c_str());
	
        
	
	

	string fileName(usr);
	addPathName(fileName,(char *)argv[argc-1],1,0,0);
	
	
	storeVal = NULL;
	filestream = fopen(fileName.c_str(),"r");
	if(filestream != NULL){
		fileNameACL.assign(fileName);
		addPathName(fileNameACL,NULL,0,1,0);

		findPermission(fileNameACL, (char *)usr.c_str(),
			       (char *)group.c_str(),&storeVal);
		if(storeVal == NULL){
			fprintf(stderr, "we have not found the user and gourp combo in the ACL\n");		
			//perror("we have not found the user and gourp combo in the ACL ");
			fprintf(stderr, " it must be the case someone has modified the ACL file\n");
			exit(EXIT_FAILURE);
		}	
		printf("the permission file is %s \n", storeVal);
		
		overWritePermission = checkPermission('w',storeVal);
		free(storeVal);
		fclose(filestream);
		if(overWritePermission != 1){
			fprintf(stderr, "we dont have overwrite permssion\n");
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
	
	
	/*
	string metaFileName(usr);
	addPathName(metaFileName,NULL,0,0,1);
	cout<<metaFileName+"TT"<<endl;
	
	
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
	}*/
	
	
	string aclListName(fileName);
	addPathName(aclListName,NULL,0,1,0);

	
	aclList = fopen(aclListName.c_str(),"w+");
	if(aclList == NULL)
		exit(EXIT_FAILURE);
	fputs(usr.c_str(),aclList);
	fputs(".*	",aclList);
	fputs("rwxpv", aclList);
	fclose(aclList);

	
	printf ("uflag = %d,aflag = %d, gflag = %d, lvalue = %d\n",
		uFlag,aFlag, gFlag, lFlag);
	printf("uval = %s, gVal = %s, aVal = %c", usr.c_str(),group.c_str(),
	       operation);
	
	
	return 0;
	
	
	
}




