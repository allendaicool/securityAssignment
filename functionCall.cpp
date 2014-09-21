//
//  functionCall.cpp
//  
//
//  Created by yihong dai on 9/20/14.
//
//
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



int checkMatch ( char *  , char *, char *, char *);
int findPermission(string & ,char *,char  *, char **);




int checkPermission(char c, char *val)
{
	int loop;
	int Permission;
	Permission = -1 ;
	for(loop = 0; loop < strlen(val);loop++)
	{
		if(val[loop] == c)
		{
			Permission = 1;
			break;
		}
	}
	if(Permission == 1)
	{
		printf("we have permission");
	}
	else
	{
		perror("we dont have  permssion");
		exit(EXIT_FAILURE);
	}
	return 1;
}
int findPermission(string &filename, char *first, char * second, char **val)
{
	ifstream infile;
	infile.open(filename);
	
	// insert code here...
    	char *token;
	char *token2;
	char *insideToken1;
	char *insideToken2;
	char * delimiter = (char *)" \t";
	//char *delimiterInside = (char *)".";
	
	string temp;
	int check;
	while(getline(infile,temp))
	{
		
		char * array = (char *)temp.c_str();
		token = strtok(array,delimiter);
		token2 =strtok(NULL,delimiter);
		
		printf("the arrays is %s \n", array);
		printf("the token is %s \n", token);
		printf("the toke2 is %s  \n" , token2);
		char *delimiterInside = (char *)".";
		insideToken1 =strtok(token,delimiterInside);
		printf("the insidetoke is %s \n",insideToken1);
		insideToken2 = strtok(NULL,delimiterInside);
		printf("the second toke is %s \n", insideToken2);
		check = checkMatch(first,second,insideToken1,insideToken2);
		if(check)
		{
			infile.close();
			*val = (char *)malloc(sizeof(char)*(strlen(token2)+1));
			strcpy(*val,token2);
			return 1;
		}
		
	}
	infile.close();
	return 0;
}

int checkMatch ( char * first , char *second, char *std1, char *std2)
{
	if(strcmp(std1,first) ==0 || strcmp(std1,"*") == 0)
	{
		if(strcmp(std2,"*")==0 || strcmp(std2, second) == 0 )
			return 1;
		else
			return 0 ;
	}
	return  0;
	
}


int parseCommand(int argc , const char ** command, int &uFlag,
		 int &gFlag,int &aFlag,
		 int &lFlag,string &usr , string & group, string &operation)
{
	int c;
	while ( (c = getopt(argc,(char * const *)command,"u:g:a:l")) != -1){
		printf("%c is answer  \n", c);
		switch(c)
		{
			case'a':
				aFlag = 1 ;
				/*(*operation)  = (char *)malloc(strlen(optarg)+1);
				 strcpy((*operation), optarg);*/
				operation.assign(optarg);
				break;
			case 'u':
				uFlag = 1;
				/*(*usr)  = (char *)malloc(strlen(optarg)+1);
				 strcpy(*usr, optarg);*/
				usr.assign(optarg);
				//printf("user is %s \n" , *usr );
				break;
			case 'g':
				gFlag = 1 ;
				/*(*group)  = (char *)malloc(strlen(optarg)+1);
				 strcpy((*group), optarg);
				 printf("group is %s \n" , *group );*/
				group.assign(optarg);
				
				break;
			case 'l':
				lFlag = 1;
				break;
				
			case '?':
				if(optopt == 'a' ||
				   optopt == 'u' || optopt == 'u')
					fprintf (stderr,
						 "Option -%c requires an argument.\n"
						 , optopt);
				else if (isprint (optopt))
					fprintf (stderr,
						 "Unknown option `-%c'.\n", optopt);
				
				else
					fprintf (stderr,
						 "werid character `\\x%x'.\n",
						 optopt);
				return 1;
				
			default:
				abort ();
		}
	}
	return 1;
}
