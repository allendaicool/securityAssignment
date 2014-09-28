//
//  objtestacl.cpp
//  
//
//  Created by yihong dai on 9/21/14.
//
//

#include "objtestacl.h"
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
	char *val;
	
	printf("arc is %d, arv[0] is %s \n", argc , argv[0]);
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0 ;
	parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
			      , group,operation);
	if(uFlag != 1 || gFlag!= 1 || aFlag != 1 || lFlag == 1){
		fprintf(stderr,"invalid argument input");
		exit(EXIT_FAILURE);
	}
	printf ("uflag = %d,aflag = %d, gflag = %d, lvalue = %d\n",
		uFlag,aFlag, gFlag, lFlag);
	printf("uval = %s, gVal = %s, aVal = %c", usr.c_str(),group.c_str(),
	       operation);

	checkifUserGroup((char *)usr.c_str(), (char *)group.c_str(),0);	

	string temp(usr);
	addPathName(temp,(char *)argv[argc-1],1,1,0);
	val = NULL;
	findPermission(temp,(char *)usr.c_str(),(char *)group.c_str(),&val);
	if(val == NULL){
		fprintf(stderr,"we have not found the user and gourp combo in the ACL ");
		fprintf(stderr," it must be the case someone has modified the ACL file");
		exit(EXIT_FAILURE);
	}
	int haveorNot  = checkPermission(operation,val);
	free(val);
	if(haveorNot!= 1)
	{
		printf("\ndenied\n");
		return 0;
	}
	printf("\nallowed\n");
	return 0;

}
