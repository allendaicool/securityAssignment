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
#include <string.h>
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
	char operation;
	int readPermission;
	char *val;
	FILE *filestream;

	printf("arc is %d, arv[0] is %s \n", argc , argv[0]);
	//char * objName = NULL;
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0 ;
	parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
			      , group,operation);
	if(uFlag != 1 || gFlag!= 1 || aFlag == 1 || lFlag == 1){
		fprintf(stderr, "invalid argument input");
		exit(EXIT_FAILURE);
	}
	printf ("uflag = %d,aflag = %d, gflag = %d, lvalue = %d\n",
		uFlag,aFlag, gFlag, lFlag);
	printf("uval = %s, gVal = %s, aVal = %c", usr.c_str(),group.c_str(),
	       operation);
	
	
	checkifUserGroup((char *)usr.c_str(), (char *)group.c_str(),0);

	
	string fileName(usr);
	addPathName(fileName,(char *)argv[argc-1],1,0,0);
	
	string fileNameACL(fileName);
	
	addPathName(fileNameACL,NULL,0,1,0);
	val = NULL;

	
	findPermission(fileNameACL, (char *)usr.c_str(),(char *)group.c_str()
		       ,&val);
	if(val == NULL){
		fprintf(stderr,"we have not found the user and gourp combo in the ACL ");
		fprintf(stderr," it must be the case someone has modified the ACL file");
		exit(EXIT_FAILURE);
	}
	printf("the permission file is %s \n", val);
	
	readPermission = checkPermission('r',val);
	free(val);
	
	
	if(readPermission == 1){
		printf("we have read permission");
		filestream = fopen(fileName.c_str(),"r");
		if(filestream == NULL){
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
			free(buffer);
		fclose(filestream);
	}
	else{
		fprintf(stderr,"we dont have read permssion");
		exit(EXIT_FAILURE);
	}
	
	return 0;
	
}
