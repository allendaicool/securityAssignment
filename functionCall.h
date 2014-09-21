//
//  functionCall.h
//  
//
//  Created by yihong dai on 9/20/14.
//
//

#ifndef ____functionCall__
#define ____functionCall__
#include<string>
using namespace std;
int parseCommand(int , const char ** , int & , int &,int &,int &,
		 string &, string &, string &);
int findPermission(string & ,char *,char  *, char **);
int checkPermission(char, char *);

#endif /* defined(____functionCall__) */
