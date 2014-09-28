//
//  objsetacl.cpp
//  
//
//  Created by yihong dai on 9/20/14.
//
//

#include "objsetacl.h"
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
	int value ;
	size_t dum;
	char * bufferReadIn;
	printf("arc is %d, arv[0] is %s \n", argc , argv[0]);
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0 ;
	parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
			      , group,operation);
	if(uFlag != 1 || gFlag!= 1 || aFlag == 1 || lFlag == 1){
		fprintf(stderr,"invalid argument input");
		exit(EXIT_FAILURE);
	}
	printf ("uflag = %d,aflag = %d, gflag = %d, lvalue = %d\n",
		uFlag,aFlag, gFlag, lFlag);
	printf("uval = %s, gVal = %s,agVal = %c", usr.c_str(),group.c_str(),
	       operation);
	if(checkShellRedirect()){
		fprintf(stderr,"There is no shell redirect. program stopped");
		exit(EXIT_FAILURE);
	}

	checkifUserGroup((char *)usr.c_str(), (char *)group.c_str(),0);
	string temp(usr);
	
	addPathName(temp,(char *)argv[argc-1],1,1,0);
	char *val = NULL;
	findPermission(temp,(char *)usr.c_str(),(char *)group.c_str(),&val);
	if(val == NULL){
		fprintf(stderr,"we have not found the user and gourp combo in the ACL ");
		fprintf(stderr," it must be the case someone has modified the ACL file");
		exit(EXIT_FAILURE);
	}
	printf("the permission file is %s \n", val);
	int haveorNot = checkPermission('p',val);
	free(val);
	if(haveorNot!= 1){
		fprintf(stderr,"do not have permission");
		exit(EXIT_FAILURE);
	}
	FILE *filestream;
	filestream = fopen(temp.c_str(),"w");
	if(filestream == NULL)
		fprintf(stderr,"something happends");
	
	bufferReadIn = NULL;
	
	while((value = (int)getline(&bufferReadIn,&dum,stdin))!=-1){
		
		printf("\n the string is %s \n",bufferReadIn);
		fputs(bufferReadIn,filestream);
		free(bufferReadIn);
		bufferReadIn = NULL;
	}
	fclose(filestream);

	
	
}
