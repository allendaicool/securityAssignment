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
	string operation;
	int result;
	
	printf("arc is %d, arv[0] is %s \n", argc , argv[0]);
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0 ;
	result = parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
			      , group,operation);
	printf ("uflag = %d,aflag = %d, gflag = %d, lvalue = %d\n",
		uFlag,aFlag, gFlag, lFlag);
	printf("uval = %s, aVal = %s, gVal = %s", usr.c_str(),group.c_str(),
	       operation.c_str());

	string temp(usr);
	/*temp.append("+");
	temp.append(argv[argc-1]);
	temp.append("+");
	temp.append("ACL");*/
	addPathName(temp,(char *)argv[argc-1],1);
	char *val = NULL;
	findPermission(temp,(char *)usr.c_str(),(char *)group.c_str(),&val);
	int haveorNot  = checkPermission(operation.c_str()[0],val);
	if(haveorNot!= 1)
	{
		printf("\ndenied\n");
		return 0;
	}
	printf("\nallowed\n");

}